#include "haflsl/nodes.hpp"
#include "haflsl/token.hpp"
#include <haflsl/transpiler.hpp>
#include <haflsl/code_buffer.hpp>
#include <iostream>

#include <spirv-tools/libspirv.h>
#include <spirv-tools/libspirv.hpp>
#include <spirv-tools/optimizer.hpp>
#include <stdexcept>
#include <string_view>
#include <bit>
#include <haflsl/lexer.hpp>

namespace HAFLSL {
    auto Transpiler::convert_ast_to_spirv(const AST& ast, const std::string_view& entrypoint_name) -> std::vector<u32> {
        CodeBuffer spirv;

        spirv.data.emplace_back(0x07230203); // magic number stolen
        spirv.data.emplace_back(0x00010300); 
        spirv.data.emplace_back(524298); // stolen too 
        spirv.data.emplace_back(0); // <-- current_id + 1
        spirv.data.emplace_back(0x00000000); // reserved

        spirv.OpCapability(ECapability::Shader);
        spirv.OpExtInstImport(spirv.register_new_id(), "GLSL.std.450");
        spirv.OpMemoryModel(EAddressingModel::Logical, EMemoryModel::GLSL450);

        struct SpvName {
            std::string_view name = {};
            u32 id = {};
        };

        std::vector<SpvName> spv_names = {};

        for(const auto& statement : ast.statements) {
            if(statement->get_type() == StatementType::DeclareFunctionStatement) {
                DeclareFunctionStatement* stmt = dynamic_cast<DeclareFunctionStatement*>(statement.get());

                if(stmt->name == entrypoint_name) {
                    spv_names.push_back({
                        .name = entrypoint_name,
                        .id = spirv.register_new_id()
                    });
                }
            }
        }

        if(spv_names.empty()) {
            throw std::runtime_error("entrypoint couldnt by found");
        }

        // MIGHT BE REMOVED
        enum struct Way : u32 {
            IN,
            OUT
        };

        struct SpvInterface {
            u32 location = {};
            Way way = {};
            TokenType type = {};
            std::string_view name = {};
            u32 id = {};
        };

        std::vector<SpvInterface> spv_interfaces = {};

        for(const auto& statement : ast.statements) {
            if(statement->get_type() == StatementType::LocationStatement) {
                LocationStatement* stmt = dynamic_cast<LocationStatement*>(statement.get());

                u32 id = spirv.register_new_id();

                spv_names.push_back({
                    .name = stmt->name,
                    .id = id
                });

                spv_interfaces.push_back( {
                    .location = stmt->location,
                    .way = (stmt->way.type == TokenType::IN) ? Way::IN : Way::OUT,
                    .type = stmt->type.type,
                    .name = stmt->name,
                    .id = id
                });
            }
        }

        auto& entrypoint = spv_names[0];

        {
            std::vector<u32> interfaces_id = {};
            interfaces_id.reserve(spv_interfaces.size() * sizeof(u32));

            for(auto interface : spv_interfaces) {
                interfaces_id.push_back(interface.id);
            }

            spirv.OpEntryPoint(EExecutionModel::Fragment, entrypoint.id, entrypoint.name, interfaces_id);
        }

        spirv.OpExecutionMode(entrypoint.id, EExecutionMode::OriginUpperLeft);
        spirv.OpSource(ESourceLanguage::GLSL, 460, 0, "");

        for(auto& statement : ast.statements) {
            if(statement->get_type() == StatementType::DeclareFunctionStatement) {
                auto* fn_stmt = dynamic_cast<DeclareFunctionStatement*>(statement.get());

                {
                    bool found = false;
                    for(auto& spv_name : spv_names) {
                        if(spv_name.name == fn_stmt->name) {
                            found = true;
                            break;
                        }
                    }

                    if(!found) {
                        u32 id = spirv.register_new_id();

                        spv_names.push_back({
                            .name = fn_stmt->name,
                            .id = id
                        });
                    }
                }

                for(auto& stmt : fn_stmt->statements) {
                    if(stmt->get_type() == StatementType::DeclareVariableStatement) {
                        auto* dc_stmt = dynamic_cast<DeclareVariableStatement*>(stmt.get());

                        bool found = false;
                        for(auto& spv_name : spv_names) {
                            if(spv_name.name == dc_stmt->name) {
                                found = true;
                                break;
                            }
                        }

                        if(!found) {
                            u32 id = spirv.register_new_id();

                            spv_names.push_back({
                                .name = dc_stmt->name,
                                .id = id
                            });
                        }
                    }
                }
            }
        }

        for(auto& name : spv_names) {
            spirv.OpName(name.id, name.name);
        }

        for(auto& interface : spv_interfaces) {
            spirv.OpDecorate(interface.id, EDecoration::Location); spirv.data.push_back(interface.location);
        }

        struct SpvTypes {
            TokenType type = {};
            bool function = false;
            u32 id = {};
        };

        std::vector<SpvTypes> spv_types = {};

        std::function<u32(Token token, bool function)> find_or_register_type;
        find_or_register_type = [&find_or_register_type, &spirv, &spv_types](Token token, bool function = false) -> u32 {
            switch(token.type) {
                case TokenType::FLOATCONSTANT: { token.type = TokenType::FLOAT; } 
                case TokenType::INTCONSTANT: { token.type = TokenType::INT; } 
                case TokenType::UINTCONSTANT: { token.type = TokenType::UINT; } 
                case TokenType::BOOLCONSTANT: { token.type = TokenType::BOOL; } 
                case TokenType::DOUBLECONSTANT: { token.type = TokenType::FLOAT; }
                default: {} 
            }
            
            for(auto& spv_type : spv_types) {
                if(spv_type.type == token.type && spv_type.function == function) {
                    return spv_type.id;
                }
            }

            u32 id = 0;
            if(function) {
                u32 fn_id = spirv.register_new_id();
                id = find_or_register_type(token, false);
                spirv.OpTypeFunction(fn_id, id);

                spv_types.push_back({
                    .type = token.type,
                    .function = function,
                    .id = fn_id
                });

                if(id == 0) { throw std::runtime_error("type id is 0"); }
                return fn_id;
            }

            id = spirv.register_new_id();
            
            switch(token.type) {
                case TokenType::BOOL: {
                    spirv.OpTypeBool(id);
                    break;   
                }

                case TokenType::FLOAT: {
                    spirv.OpTypeFloat(id, 32);
                    break;   
                }

                case TokenType::INT: {
                    spirv.OpTypeInt(id, 32, 1);
                    break;   
                }

                case TokenType::UINT: {
                    spirv.OpTypeInt(id, 32, 0);
                    break;   
                }

                case TokenType::DOUBLE: {
                    spirv.OpTypeFloat(id, 32);
                    break;   
                }

                case TokenType::BVEC2: {
                    u32 type_id = find_or_register_type({ .type = TokenType::BOOL }, false);
                    spirv.OpTypeVector(id, type_id, 2);
                    break;   
                }

                case TokenType::BVEC3: {
                    u32 type_id = find_or_register_type({ .type = TokenType::BOOL }, false);
                    spirv.OpTypeVector(id, type_id, 3);
                    break;   
                }

                case TokenType::BVEC4: {
                    u32 type_id = find_or_register_type({ .type = TokenType::BOOL }, false);
                    spirv.OpTypeVector(id, type_id, 4);
                    break;   
                }

                case TokenType::IVEC2: {
                    u32 type_id = find_or_register_type({ .type = TokenType::INT }, false);
                    spirv.OpTypeVector(id, type_id, 2);
                    break;   
                }

                case TokenType::IVEC3: {
                    u32 type_id = find_or_register_type({ .type = TokenType::INT }, false);
                    spirv.OpTypeVector(id, type_id, 3);
                    break;   
                }

                case TokenType::IVEC4: {
                    u32 type_id = find_or_register_type({ .type = TokenType::INT }, false);
                    spirv.OpTypeVector(id, type_id, 4);
                    break;   
                }

                case TokenType::UVEC2: {
                    u32 type_id = find_or_register_type({ .type = TokenType::UINT }, false);
                    spirv.OpTypeVector(id, type_id, 2);
                    break;   
                }

                case TokenType::UVEC3: {
                    u32 type_id = find_or_register_type({ .type = TokenType::UINT }, false);
                    spirv.OpTypeVector(id, type_id, 3);
                    break;   
                }

                case TokenType::UVEC4: {
                    u32 type_id = find_or_register_type({ .type = TokenType::UINT }, false);
                    spirv.OpTypeVector(id, type_id, 4);
                    break;   
                }

                case TokenType::VEC2: {
                    u32 type_id = find_or_register_type({ .type = TokenType::FLOAT }, false);
                    spirv.OpTypeVector(id, type_id, 2);
                    break;   
                }

                case TokenType::VEC3: {
                    u32 type_id = find_or_register_type({ .type = TokenType::FLOAT }, false);
                    spirv.OpTypeVector(id, type_id, 3);
                    break;   
                }

                case TokenType::VEC4: {
                    u32 type_id = find_or_register_type({ .type = TokenType::FLOAT }, false);
                    spirv.OpTypeVector(id, type_id, 4);
                    break;   
                }

                case TokenType::MAT2: {
                    u32 type_id = find_or_register_type({ .type = TokenType::VEC2 }, false);
                    spirv.OpTypeMatrix(id, type_id, 2);
                    break;   
                }

                case TokenType::MAT3: {
                    u32 type_id = find_or_register_type({ .type = TokenType::VEC3 }, false);
                    spirv.OpTypeMatrix(id, type_id, 3);
                    break;   
                }

                case TokenType::MAT4: {
                    u32 type_id = find_or_register_type({ .type = TokenType::VEC4 }, false);
                    spirv.OpTypeMatrix(id, type_id, 4);
                    break;   
                }

                case TokenType::MAT2X2: {
                    u32 type_id = find_or_register_type({ .type = TokenType::VEC2 }, false);
                    spirv.OpTypeMatrix(id, type_id, 2);
                    break;   
                }

                case TokenType::MAT2X3: {
                    u32 type_id = find_or_register_type({ .type = TokenType::VEC3 }, false);
                    spirv.OpTypeMatrix(id, type_id, 2);
                    break;   
                }

                case TokenType::MAT2X4: {
                    u32 type_id = find_or_register_type({ .type = TokenType::VEC4 }, false);
                    spirv.OpTypeMatrix(id, type_id, 2);
                    break;   
                }

                case TokenType::MAT3X2: {
                    u32 type_id = find_or_register_type({ .type = TokenType::VEC2 }, false);
                    spirv.OpTypeMatrix(id, type_id, 3);
                    break;   
                }

                case TokenType::MAT3X3: {
                    u32 type_id = find_or_register_type({ .type = TokenType::VEC3 }, false);
                    spirv.OpTypeMatrix(id, type_id, 3);
                    break;   
                }

                case TokenType::MAT3X4: {
                    u32 type_id = find_or_register_type({ .type = TokenType::VEC4 }, false);
                    spirv.OpTypeMatrix(id, type_id, 3);
                    break;   
                }

                case TokenType::MAT4X2: {
                    u32 type_id = find_or_register_type({ .type = TokenType::VEC2 }, false);
                    spirv.OpTypeMatrix(id, type_id, 4);
                    break;   
                }

                case TokenType::MAT4X3: {
                    u32 type_id = find_or_register_type({ .type = TokenType::VEC3 }, false);
                    spirv.OpTypeMatrix(id, type_id, 4);
                    break;   
                }

                case TokenType::MAT4X4: {
                    u32 type_id = find_or_register_type({ .type = TokenType::VEC4 }, false);
                    spirv.OpTypeMatrix(id, type_id, 4);
                    break;   
                }

                case TokenType::DVEC2: {
                    u32 type_id = find_or_register_type({ .type = TokenType::FLOAT}, false);
                    spirv.OpTypeVector(id, type_id, 2);
                    break;   
                }

                case TokenType::DVEC3: {
                    u32 type_id = find_or_register_type({ .type = TokenType::FLOAT}, false);
                    spirv.OpTypeVector(id, type_id, 3);
                    break;   
                }

                case TokenType::DVEC4: {
                    u32 type_id = find_or_register_type({ .type = TokenType::FLOAT}, false);
                    spirv.OpTypeVector(id, type_id, 4);
                    break;   
                }

                case TokenType::DMAT2: {
                    u32 type_id = find_or_register_type({ .type = TokenType::DVEC2 }, false);
                    spirv.OpTypeMatrix(id, type_id, 2);
                    break;   
                }

                case TokenType::DMAT3: {
                    u32 type_id = find_or_register_type({ .type = TokenType::DVEC3 }, false);
                    spirv.OpTypeMatrix(id, type_id, 3);
                    break;   
                }

                case TokenType::DMAT4: {
                    u32 type_id = find_or_register_type({ .type = TokenType::DVEC4 }, false);
                    spirv.OpTypeMatrix(id, type_id, 4);
                    break;   
                }

                case TokenType::DMAT2X2: {
                    u32 type_id = find_or_register_type({ .type = TokenType::DVEC2 }, false);
                    spirv.OpTypeMatrix(id, type_id, 2);
                    break;   
                }

                case TokenType::DMAT2X3: {
                    u32 type_id = find_or_register_type({ .type = TokenType::DVEC3 }, false);
                    spirv.OpTypeMatrix(id, type_id, 2);
                    break;   
                }

                case TokenType::DMAT2X4: {
                    u32 type_id = find_or_register_type({ .type = TokenType::DVEC4 }, false);
                    spirv.OpTypeMatrix(id, type_id, 2);
                    break;   
                }

                case TokenType::DMAT3X2: {
                    u32 type_id = find_or_register_type({ .type = TokenType::DVEC2 }, false);
                    spirv.OpTypeMatrix(id, type_id, 3);
                    break;   
                }

                case TokenType::DMAT3X3: {
                    u32 type_id = find_or_register_type({ .type = TokenType::DVEC3 }, false);
                    spirv.OpTypeMatrix(id, type_id, 3);
                    break;   
                }

                case TokenType::DMAT3X4: {
                    u32 type_id = find_or_register_type({ .type = TokenType::DVEC4 }, false);
                    spirv.OpTypeMatrix(id, type_id, 3);
                    break;   
                }

                case TokenType::DMAT4X2: {
                    u32 type_id = find_or_register_type({ .type = TokenType::DVEC2 }, false);
                    spirv.OpTypeMatrix(id, type_id, 4);
                    break;   
                }

                case TokenType::DMAT4X3: {
                    u32 type_id = find_or_register_type({ .type = TokenType::DVEC3 }, false);
                    spirv.OpTypeMatrix(id, type_id, 4);
                    break;   
                }

                case TokenType::DMAT4X4: {
                    u32 type_id = find_or_register_type({ .type = TokenType::DVEC4 }, false);
                    spirv.OpTypeMatrix(id, type_id, 4);
                    break;   
                }

                case TokenType::VOID: {
                    spirv.OpTypeVoid(id);
                    break;   
                }

                default: {
                    throw std::runtime_error("bad token type");
                }
            };

            spv_types.push_back({
                .type = token.type,
                .function = function,
                .id = id
            });

            if(id == 0) { throw std::runtime_error("type id is 0"); }
            return id;
        };

        for(auto& statement : ast.statements) {
            if(statement->get_type() == StatementType::DeclareFunctionStatement) {
                DeclareFunctionStatement* fn = dynamic_cast<DeclareFunctionStatement*>(statement.get());

                u32 type_id = find_or_register_type(Token { .type = fn->returned_type.type }, true);
            }

            if(statement->get_type() == StatementType::LocationStatement) {
                LocationStatement* stmt = dynamic_cast<LocationStatement*>(statement.get());

                u32 type_id = find_or_register_type(Token { .type = stmt->type.type }, false);
            }
        }

        struct SpvPointer {
            EStorageClass storage_class = {};
            TokenType type = {};
            u32 id = {};
        };

        std::vector<SpvPointer> spv_pointers = {};

        for(const auto& statement : ast.statements) {
            if(statement->get_type() == StatementType::LocationStatement) {
                LocationStatement* stmt = dynamic_cast<LocationStatement*>(statement.get());

                bool found = false;
                for(auto& pointer : spv_pointers) {
                    if(pointer.storage_class == EStorageClass::Output && pointer.type == stmt->type.type) {
                        found = true;
                    }
                }

                if(!found) {
                    u32 id = spirv.register_new_id();
                    spv_pointers.push_back({
                        .storage_class = EStorageClass::Output,
                        .type = stmt->type.type,
                        .id = id
                    });

                    u32 type_id = find_or_register_type(Token { .type = stmt->type.type}, false);

                    spirv.OpTypePointer(id, EStorageClass::Output, type_id);
                }
            }

            if(statement->get_type() == StatementType::DeclareFunctionStatement) {
                auto* fn_stmt = dynamic_cast<DeclareFunctionStatement*>(statement.get());

                for(auto& stmt : fn_stmt->statements) {
                    if(stmt->get_type() == StatementType::DeclareVariableStatement) {
                        auto* dc_stmt = dynamic_cast<DeclareVariableStatement*>(stmt.get());

                        bool found = false;
                        for(auto& pointer : spv_pointers) {
                            if(pointer.storage_class == EStorageClass::Function && pointer.type == dc_stmt->type.type) {
                                found = true;
                            }
                        }

                        if(!found) {
                            u32 id = spirv.register_new_id();
                            spv_pointers.push_back({
                                .storage_class = EStorageClass::Function,
                                .type = dc_stmt->type.type,
                                .id = id
                            });

                            u32 type_id = find_or_register_type(Token { .type = dc_stmt->type.type}, false);

                            spirv.OpTypePointer(id, EStorageClass::Function, type_id);
                        }
                    }
                }
            }
        }

        struct SpvVariable {
            std::string_view name = {};
            EStorageClass storage_class = {};
            TokenType type = {};
            u32 id = {};
        };

        std::vector<SpvVariable> spv_variables = {};

        for(const auto& statement : ast.statements) {
            if(statement->get_type() == StatementType::LocationStatement) {
                LocationStatement* stmt = dynamic_cast<LocationStatement*>(statement.get());

                bool found = false;
                for(auto& pointer : spv_variables) {
                    if(pointer.storage_class == EStorageClass::Output && pointer.type == stmt->type.type) {
                        found = true;
                    }
                }

                if(!found) {
                    u32 id = 0;
                    for(auto& name : spv_names) {
                        if(name.name == stmt->name) {
                            id = name.id;
                        }
                    }

                    if(id == 0) {
                        throw std::runtime_error("kys");
                    }

                    spv_variables.push_back({
                        .name = stmt->name,
                        .storage_class = EStorageClass::Output,
                        .type = stmt->type.type,
                        .id = id
                    });

                    u32 type_id = 0;
                    for(auto& type : spv_pointers) {
                        if(type.type == stmt->type.type) {
                            type_id = type.id;
                            break;
                        }
                    }

                    spirv.OpVariable(type_id, id, EStorageClass::Output, 0);
                }
            }
        }

        auto convert_value_into_bits = [](const Token& token) -> std::pair<TokenType, u32> {
            TokenType type = token.type;
            u32 value = 0;

            switch(type) {
                case TokenType::FLOATCONSTANT: { 
                    type = TokenType::FLOAT; 
                    value = std::bit_cast<u32>(static_cast<f32>(std::get<f64>(token.data)));
                    break;
                }

                case TokenType::INTCONSTANT: { 
                    type = TokenType::INT; 
                    value = std::bit_cast<u32>(static_cast<i32>(std::get<i64>(token.data)));
                    break;
                }

                case TokenType::UINTCONSTANT: { 
                    type = TokenType::UINT; 
                    value = std::bit_cast<u32>(static_cast<u32>(std::get<u64>(token.data)));
                    break;
                }

                case TokenType::BOOLCONSTANT: { 
                    type = TokenType::BOOL; 
                    value = std::get<bool>(token.data) ? 1 : 0;
                    break;
                }

                case TokenType::DOUBLECONSTANT: { 
                    type = TokenType::FLOAT; 
                    value = std::bit_cast<u32>(static_cast<f32>(std::get<f64>(token.data)));
                    break;
                }

                default: { throw std::runtime_error("not handled type"); } 
            }

            return {type, value};
        };

        struct SpvConstant {
            TokenType type = {};
            std::vector<u32> values = {};
            std::vector<UUID> uuids = {};
            u32 id = {};
        };

        std::vector<SpvConstant> spv_constants = {};

        std::function<u32(const std::unique_ptr<Expression>& expr)> find_or_register_constant;
        find_or_register_constant = [&find_or_register_constant, &spirv, &spv_constants, &spv_types, &find_or_register_type, &convert_value_into_bits](const std::unique_ptr<Expression>& expr) -> u32 {
            for(auto& spv_constant : spv_constants) {
                for(auto& uuid : spv_constant.uuids) {
                    if(expr->uuid == uuid) {
                        return spv_constant.id;
                    }
                }
            }

            TokenType type = {};
            std::vector<u32> values = {};
            if(expr->get_type() == ExpressionType::ConstantValueExpression) {
                auto* e = dynamic_cast<ConstantValueExpression*>(expr.get());
                type = e->token.type;
                auto pair = convert_value_into_bits(e->token);
                type = pair.first;
                values.push_back(pair.second);
            } else if(expr->get_type() == ExpressionType::ConstructorExpression) {
                auto* e = dynamic_cast<ConstructorExpression*>(expr.get());
                type = e->type.type;
                for(auto& value : e->values) {
                    auto* v = dynamic_cast<ConstantValueExpression*>(value.get());
                    values.push_back(convert_value_into_bits(v->token).second);
                }
            } else {
                throw std::runtime_error("wrong type of expression");
            }
            
            for(auto& spv_constant : spv_constants) {
                if(spv_constant.type == type) {
                    for(u32 i = 0; i < spv_constant.values.size(); i++) {
                        if(values[i] != spv_constant.values[i]) {
                            break;
                        }

                        if(i == spv_constant.values.size() - 1) {
                            spv_constant.uuids.push_back(expr->uuid);
                            return spv_constant.id;
                        }
                    }
                }
            }

            u32 id = spirv.register_new_id();
            if(expr->get_type() == ExpressionType::ConstantValueExpression) {
                u32 type_id = find_or_register_type({ .type = type }, false);

                if(type != TokenType::BOOL) {
                    spirv.OpConstant(type_id, id, values);
                } else {
                    if(values[0]) {
                        spirv.OpConstantTrue(type_id, id);
                    } else if(!values[0]) {
                        spirv.OpConstantFalse(type_id, id);
                    } else {
                        throw std::runtime_error("wrong type of value");
                    }
                }

            } else if(expr->get_type() == ExpressionType::ConstructorExpression) {
                auto* e = dynamic_cast<ConstructorExpression*>(expr.get());
                type = e->type.type;

                std::vector<u32> ids = {};
                for(auto& v : e->values) {
                    ids.push_back(find_or_register_constant(v));
                }

                switch(type) {
                    case TokenType::VEC4: {
                        u32 type_id = find_or_register_type({ .type = TokenType::VEC4 }, false);
                        spirv.OpConstantComposite(type_id, id, ids);
                        break;
                    }
                    default: {}
                }
            } else {
                throw std::runtime_error("wrong type of expression");
            }

            spv_constants.push_back({
                .type = type,
                .values = values,
                .uuids = { expr->uuid },
                .id = id,
            });

            return id;
        };

        // CONSTANTS
        for(auto& statement : ast.statements) {
            if(statement->get_type() == StatementType::DeclareFunctionStatement) {
                DeclareFunctionStatement* stmt = dynamic_cast<DeclareFunctionStatement*>(statement.get());

                for(auto& st : stmt->statements) {
                    if(st->get_type() == StatementType::ExpressionStatement) {
                        ExpressionStatement* expr_stmt = dynamic_cast<ExpressionStatement*>(st.get());
                        
                        if(expr_stmt->expression->get_type() == ExpressionType::AssignExpression) {
                            AssignExpression* assign_expr = dynamic_cast<AssignExpression*>(expr_stmt->expression.get());

                            if(assign_expr->right->get_type() == ExpressionType::ConstructorExpression) {
                                u32 constant_id = find_or_register_constant(assign_expr->right);
                            }
                        }
                    }

                    if(st->get_type() == StatementType::DeclareVariableStatement) {
                        auto* dc_stmt = dynamic_cast<DeclareVariableStatement*>(st.get());

                        if(dc_stmt->expression->get_type() == ExpressionType::ConstantValueExpression) {
                            u32 constant_id = find_or_register_constant(dc_stmt->expression);
                        }

                        if(dc_stmt->expression->get_type() == ExpressionType::ConstructorExpression) {
                            u32 constant_id = find_or_register_constant(dc_stmt->expression);
                        }
                    } else if(st->get_type() == StatementType::ReturnStatement){
                        auto* rt_stmt = dynamic_cast<ReturnStatement*>(st.get());
                        if(rt_stmt->expr->get_type() == ExpressionType::ConstantValueExpression) {
                            u32 constant_id = find_or_register_constant(rt_stmt->expr);
                        }
                    }
                }
            }
        }


        // FUNCTIONS
        for(auto& statement : ast.statements) {
            if(statement->get_type() == StatementType::DeclareFunctionStatement) {
                DeclareFunctionStatement* fn_stmt = dynamic_cast<DeclareFunctionStatement*>(statement.get());

                u32 return_type_id = find_or_register_type(Token { .type = fn_stmt->returned_type.type}, false);
                u32 function_type_id = find_or_register_type(Token { .type = fn_stmt->returned_type.type}, true);

                u32 name_id = 0;
                for(auto& name : spv_names) {
                    if(name.name == fn_stmt->name) {
                        name_id = name.id;
                        break;
                    }
                }

                spirv.OpFunction(return_type_id, name_id, EFunctionControl::None, function_type_id);
                spirv.OpLabel(spirv.register_new_id());

                for(auto& st : fn_stmt->statements) {
                    if(st->get_type() == StatementType::ExpressionStatement) {
                        auto* expr_stmt = dynamic_cast<ExpressionStatement*>(st.get());
                        
                        /*if(expr_stmt->expression->get_type() == ExpressionType::AssignExpression) {
                            auto* assign_expr = dynamic_cast<AssignExpression*>(expr_stmt->expression.get()); 

                            auto* left_expr = dynamic_cast<ConstantValueExpression*>(assign_expr->left.get()); 

                            u32 name_id = 0;
                            for(auto& name : spv_names) {
                                if(name.name == std::get<std::string_view>(left_expr->token.data)) {
                                    name_id = name.id;
                                    break;
                                }
                            }

                            u32 object_id = 0;
                            if(assign_expr->right->get_type() == ExpressionType::ConstructorExpression) {
                                for(auto& spv_composite : spv_constant_composites) {
                                    for(auto& uuid : spv_composite.uuids) {
                                        if(assign_expr->right->uuid == uuid) {
                                            object_id = spv_composite.id;
                                            break;
                                        }
                                    }

                                    if(object_id != 0) {
                                        break;
                                    }
                                }
                            }


                            spirv.OpStore(name_id, object_id);
                        }*/
                    }  else if(st->get_type() == StatementType::DeclareVariableStatement) {
                        auto* dc_stmt = dynamic_cast<DeclareVariableStatement*>(st.get());

                        u32 id = 0;
                        for(auto& name : spv_names) {
                            if(name.name == dc_stmt->name) {
                                id = name.id;
                            }
                        }

                        if(id == 0) {
                            throw std::runtime_error("kys");
                        }

                        spv_variables.push_back({
                            .name = dc_stmt->name,
                            .storage_class = EStorageClass::Function,
                            .type = dc_stmt->type.type,
                            .id = id
                        });

                        u32 type_id = 0;
                        for(auto& type : spv_pointers) {
                            if(type.type == dc_stmt->type.type && type.storage_class == EStorageClass::Function) {
                                type_id = type.id;
                                break;
                            }
                        }

                        spirv.OpVariable(type_id, id, EStorageClass::Function, 0);
                    }
                }

                // OPERATIONS

                for(auto& st : fn_stmt->statements) {
                    if(st->get_type() == StatementType::ExpressionStatement) {
                        auto* expr_stmt = dynamic_cast<ExpressionStatement*>(st.get());
                        
                        if(expr_stmt->expression->get_type() == ExpressionType::AssignExpression) {
                            auto* assign_expr = dynamic_cast<AssignExpression*>(expr_stmt->expression.get()); 
                            auto* left_expr = dynamic_cast<ConstantValueExpression*>(assign_expr->left.get()); 

                            u32 id = 0;
                            for(auto& name : spv_names) {
                                if(name.name == std::get<std::string_view>(left_expr->token.data)) {
                                    id = name.id;
                                    break;
                                }
                            }

                            if(assign_expr->right->get_type() == ExpressionType::ConstructorExpression) {
                                u32 object_id = find_or_register_constant(assign_expr->right);
                                
                                spirv.OpStore(id, object_id);
                            }

                            if(assign_expr->right->get_type() == ExpressionType::ConstantValueExpression) {
                                auto* cons_expr = dynamic_cast<ConstantValueExpression*>(assign_expr->right.get());
                                if(cons_expr->token.type == TokenType::IDENTIFIER) {
                                    std::string_view v_name = std::get<std::string_view>(cons_expr->token.data);

                                    u32 loaded_id = 0;
                                    TokenType loaded_type = {};
                                    for(auto& spv_variable : spv_variables) {
                                        if(spv_variable.name == v_name) {
                                            loaded_id = spv_variable.id;
                                            loaded_type = spv_variable.type;
                                            break;
                                        }
                                    }

                                    u32 loaded_type_id = 0;
                                    for(auto& type : spv_types) {
                                        if(type.type == loaded_type && type.function == false) {
                                            loaded_type_id = type.id;
                                            break;
                                        }
                                    }

                                    u32 temp_id = spirv.register_new_id();
                                    spirv.OpLoad(loaded_type_id, temp_id, loaded_id);
                                    spirv.OpStore(id, temp_id);
                                } else if(cons_expr->token.type == TokenType::DOUBLECONSTANT) {
                                    u32 value_id = find_or_register_constant(assign_expr->right);

                                    spirv.OpStore(id, value_id);
                                } else if(cons_expr->token.type == TokenType::FLOATCONSTANT) {
                                    u32 value_id = find_or_register_constant(assign_expr->right);

                                    spirv.OpStore(id, value_id);
                                }
                            }
                        }
                    }  else if(st->get_type() == StatementType::DeclareVariableStatement) {
                        auto* dc_stmt = dynamic_cast<DeclareVariableStatement*>(st.get());

                        u32 id = 0;
                        for(auto& name : spv_names) {
                            if(name.name == dc_stmt->name) {
                                id = name.id;
                                break;
                            }
                        }

                        if(dc_stmt->expression->get_type() == ExpressionType::ConstructorExpression) {
                            u32 value_id = find_or_register_constant(dc_stmt->expression);

                            spirv.OpStore(id, value_id);
                        }

                        if(dc_stmt->expression->get_type() == ExpressionType::ConstantValueExpression) {
                            auto* cons_expr = dynamic_cast<ConstantValueExpression*>(dc_stmt->expression.get());
                            if(cons_expr->token.type == TokenType::IDENTIFIER) {
                                std::string_view v_name = std::get<std::string_view>(cons_expr->token.data);

                                u32 loaded_id = 0;
                                TokenType loaded_type = {};
                                for(auto& spv_variable : spv_variables) {
                                    if(spv_variable.name == v_name) {
                                        loaded_id = spv_variable.id;
                                        loaded_type = spv_variable.type;
                                        break;
                                    }
                                }

                                u32 loaded_type_id = 0;
                                for(auto& type : spv_types) {
                                    if(type.type == dc_stmt->type.type && type.function == false) {
                                        loaded_type_id = type.id;
                                        break;
                                    }
                                }

                                u32 temp_id = spirv.register_new_id();
                                spirv.OpLoad(loaded_type_id, temp_id, loaded_id);
                                spirv.OpStore(id, temp_id);
                            } else if(cons_expr->token.type == TokenType::FLOATCONSTANT || cons_expr->token.type == TokenType::DOUBLECONSTANT) {
                                u32 value_id = find_or_register_constant(dc_stmt->expression);

                                if(value_id == 0) {
                                    throw std::runtime_error("dwadwa");
                                }

                                spirv.OpStore(id, value_id);
                            }
                        }

                        if(dc_stmt->expression->get_type() == ExpressionType::CallFunctionExpression) {
                            auto* cfn_expr = dynamic_cast<CallFunctionExpression*>(dc_stmt->expression.get());
                            auto* cons_expr = dynamic_cast<ConstantValueExpression*>(cfn_expr->function_expr.get());
                            u32 function_id = 0;
                            for(auto& name : spv_names) {
                                if(name.name == std::get<std::string_view>(cons_expr->token.data)) {
                                    function_id = name.id;
                                    break;
                                }
                            }

                            u32 type_id = find_or_register_type(Token { .type = dc_stmt->type.type}, false);
                            
                            u32 result_id = spirv.register_new_id();
                            spirv.OpFunctionCall(type_id, result_id, function_id);   
                            spirv.OpStore(id, result_id);
                        
                        }
                    } else if(st->get_type() == StatementType::ReturnStatement){
                        auto* rt_stmt = dynamic_cast<ReturnStatement*>(st.get());
                        if(rt_stmt->expr->get_type() == ExpressionType::ConstantValueExpression) {
                            u32 value_id = find_or_register_constant(rt_stmt->expr);

                            spirv.OpReturnValue(value_id);
                        }
                    }
                }

                if(fn_stmt->returned_type.type == TokenType::VOID) {
                    spirv.OpReturn();
                }

                spirv.OpFunctionEnd();
            }
        }

        spirv.data[3] = spirv.current_id + 1;

        spvtools::SpirvTools core(SPV_ENV_UNIVERSAL_1_3);

        auto print_msg_to_stderr = [](spv_message_level_t, const char*, const spv_position_t&, const char* m) {
            std::cerr << "spirv validator error: " << m << std::endl;
        };

        core.SetMessageConsumer(print_msg_to_stderr);

        core.Validate(spirv.data);

        std::string spirv_disassmble = {};

        core.Disassemble(spirv.data, &spirv_disassmble);

        //std::cout << spirv_disassmble << std::endl;

        //throw std::runtime_error("bruh");

        /*std::ofstream file;
        file.open("shader.bin", std::ios::binary | std::ios::out);
        file.write(reinterpret_cast<char*>(spirv.data.data()), spirv.data.size() * sizeof(uint32_t));
        file.close();*/

        return spirv.data;
    }
}