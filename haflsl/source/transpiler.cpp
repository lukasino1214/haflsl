#include "haflsl/nodes.hpp"
#include "haflsl/token.hpp"
#include <haflsl/transpiler.hpp>
#include <haflsl/code_buffer.hpp>
#include <iostream>

#include <memory>
#include <spirv-tools/libspirv.h>
#include <spirv-tools/libspirv.hpp>
#include <spirv-tools/optimizer.hpp>
#include <stdexcept>
#include <string_view>
#include <bit>
#include <haflsl/lexer.hpp>
#include <variant>

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

        auto find_or_register_name = [&spv_names, &spirv](const std::string_view& name) -> u32 {
            for(auto& spv_name : spv_names) {
                if(spv_name.name == name) {
                    return spv_name.id;
                }
            }

            throw std::runtime_error("name wasnt registered");

            return 0;
        };

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
                    u32 id = find_or_register_name(stmt->name);

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

        struct BinaryResult {
            TokenType type;
            std::variant<std::monostate, std::vector<i64>, std::vector<f64>> data = std::monostate{};
        };

        enum struct BinaryMathOpType: u32 {
            SAME = 0, // type == type
            LEFT = 1, // f32 * vec3
            RIGHT = 2 // vec3 * f32
        };

        auto math_op = []<typename T1, typename T2>(BinaryResult& left_result, BinaryResult& right_result, BinaryType op, BinaryMathOpType type) -> BinaryResult {
            if (type == BinaryMathOpType::SAME) {
                std::vector<T1> values = {};
                std::vector<T1>& left_values = std::get<std::vector<T1>>(left_result.data);
                std::vector<T1>& right_values = std::get<std::vector<T1>>(right_result.data);

                for(u32 i = 0; i < left_values.size(); i++) {
                    switch(op) {
                        case BinaryType::Multiply: { values.push_back(static_cast<T1>(static_cast<T2>(left_values[i]) * static_cast<T2>(right_values[i]))); break; }
                        case BinaryType::Divide:   { values.push_back(static_cast<T1>(static_cast<T2>(left_values[i]) / static_cast<T2>(right_values[i]))); break; }
                        case BinaryType::Add:      { values.push_back(static_cast<T1>(static_cast<T2>(left_values[i]) + static_cast<T2>(right_values[i]))); break; }
                        case BinaryType::Subtract: { values.push_back(static_cast<T1>(static_cast<T2>(left_values[i]) - static_cast<T2>(right_values[i]))); break; }
                        default: { throw std::runtime_error("unhandled binary operation"); }
                    }
                }

                BinaryResult result;
                result.type = left_result.type;
                result.data = values;
                return result;
            } else if(type == BinaryMathOpType::LEFT) {
                std::vector<T1> values = {};
                std::vector<T1>& left_values = std::get<std::vector<T1>>(left_result.data);
                std::vector<T1>& right_values = std::get<std::vector<T1>>(right_result.data);

                for(u32 i = 0; i < right_values.size(); i++) {
                    switch(op) {
                        case BinaryType::Multiply: { values.push_back(static_cast<T1>(static_cast<T2>(left_values[0]) * static_cast<T2>(right_values[i]))); break; }
                        case BinaryType::Divide:   { values.push_back(static_cast<T1>(static_cast<T2>(left_values[0]) / static_cast<T2>(right_values[i]))); break; }
                        case BinaryType::Add:      { values.push_back(static_cast<T1>(static_cast<T2>(left_values[0]) + static_cast<T2>(right_values[i]))); break; }
                        case BinaryType::Subtract: { values.push_back(static_cast<T1>(static_cast<T2>(left_values[0]) - static_cast<T2>(right_values[i]))); break; }
                        default: { throw std::runtime_error("unhandled binary operation"); }
                    }
                }

                BinaryResult result;
                result.type = right_result.type;
                result.data = values;
                return result;
            } else if(type == BinaryMathOpType::RIGHT) {
                std::vector<T1> values = {};
                std::vector<T1>& left_values = std::get<std::vector<T1>>(left_result.data);
                std::vector<T1>& right_values = std::get<std::vector<T1>>(right_result.data);

                for(u32 i = 0; i < left_values.size(); i++) {
                    switch(op) {
                        case BinaryType::Multiply: { values.push_back(static_cast<T1>(static_cast<T2>(left_values[i]) * static_cast<T2>(right_values[0]))); break; }
                        case BinaryType::Divide:   { values.push_back(static_cast<T1>(static_cast<T2>(left_values[i]) / static_cast<T2>(right_values[0]))); break; }
                        case BinaryType::Add:      { values.push_back(static_cast<T1>(static_cast<T2>(left_values[i]) + static_cast<T2>(right_values[0]))); break; }
                        case BinaryType::Subtract: { values.push_back(static_cast<T1>(static_cast<T2>(left_values[i]) - static_cast<T2>(right_values[0]))); break; }
                        default: { throw std::runtime_error("unhandled binary operation"); }
                    }
                }

                BinaryResult result;
                result.type = left_result.type;
                result.data = values;
                return result;
            }

            return {};
        };

        std::function<BinaryResult(Expression* expr)> look_binary_expression;
        look_binary_expression = [&look_binary_expression, &math_op](Expression* expr) -> BinaryResult {
            if(expr->get_type() == ExpressionType::BinaryExpression) {
                auto* bin_expr = dynamic_cast<BinaryExpression*>(expr);

                BinaryResult left_result = look_binary_expression(bin_expr->left.get());
                BinaryResult right_result = look_binary_expression(bin_expr->right.get());
                BinaryResult result;

                if(left_result.type == right_result.type) {
                    result.type = left_result.type;

                    switch(result.type) {
                        case TokenType::FLOATCONSTANT: {
                            result = math_op.template operator()<f64, f64>(left_result, right_result, bin_expr->type, BinaryMathOpType::SAME);
                            break;
                        }

                        case TokenType::INTCONSTANT: {
                            result = math_op.template operator()<i64, i64>(left_result, right_result, bin_expr->type, BinaryMathOpType::SAME);
                            break;
                        }

                        case TokenType::UINTCONSTANT: {
                            result = math_op.template operator()<i64, u64>(left_result, right_result, bin_expr->type, BinaryMathOpType::SAME);
                            break;
                        }

                        case TokenType::DOUBLECONSTANT: {
                            result = math_op.template operator()<f64, f64>(left_result, right_result, bin_expr->type, BinaryMathOpType::SAME);
                            break;
                        }

                        case TokenType::IVEC2 ... TokenType::IVEC4: { 
                            result = math_op.template operator()<i64, i64>(left_result, right_result, bin_expr->type, BinaryMathOpType::SAME);
                            break;
                        }

                        case TokenType::UVEC2 ... TokenType::UVEC4: { 
                            result = math_op.template operator()<i64, u64>(left_result, right_result, bin_expr->type, BinaryMathOpType::SAME);
                            break;
                        }

                        case TokenType::VEC2 ... TokenType::VEC4: {
                            result = math_op.template operator()<f64, f64>(left_result, right_result, bin_expr->type, BinaryMathOpType::SAME);
                            break;
                        }

                        case TokenType::DVEC2 ... TokenType::DVEC4: { 
                            result = math_op.template operator()<f64, f64>(left_result, right_result, bin_expr->type, BinaryMathOpType::SAME);
                            break;
                        }

                        default: { throw std::runtime_error("hmmmmm"); }
                    }
                } else { 
                    if((left_result.type == TokenType::IVEC2 || left_result.type == TokenType::IVEC3 || left_result.type == TokenType::IVEC4) && right_result.type == TokenType::INTCONSTANT) {
                        result = math_op.template operator()<i64, i64>(left_result, right_result, bin_expr->type, BinaryMathOpType::RIGHT);
                    } else if((left_result.type == TokenType::UVEC2 || left_result.type == TokenType::UVEC3 || left_result.type == TokenType::UVEC4) && right_result.type == TokenType::UINTCONSTANT) {
                        result = math_op.template operator()<i64, u64>(left_result, right_result, bin_expr->type, BinaryMathOpType::RIGHT);
                    } else if((left_result.type == TokenType::VEC2 || left_result.type == TokenType::VEC3 || left_result.type == TokenType::VEC4) && (right_result.type == TokenType::FLOATCONSTANT || right_result.type == TokenType::DOUBLECONSTANT)) {
                        result = math_op.template operator()<f64, f64>(left_result, right_result, bin_expr->type, BinaryMathOpType::RIGHT);
                    } else if((left_result.type == TokenType::DVEC2 || left_result.type == TokenType::DVEC3 || left_result.type == TokenType::DVEC4) && (right_result.type == TokenType::FLOATCONSTANT || right_result.type == TokenType::DOUBLECONSTANT)) {
                        result = math_op.template operator()<f64, f64>(left_result, right_result, bin_expr->type, BinaryMathOpType::RIGHT);
                    } 
                    
                    else if((right_result.type == TokenType::IVEC2 || right_result.type == TokenType::IVEC3 || right_result.type == TokenType::IVEC4) && left_result.type == TokenType::INTCONSTANT) {
                        result = math_op.template operator()<i64, i64>(left_result, right_result, bin_expr->type, BinaryMathOpType::LEFT);
                    } else if((right_result.type == TokenType::UVEC2 || right_result.type == TokenType::UVEC3 || right_result.type == TokenType::UVEC4) && left_result.type == TokenType::UINTCONSTANT) {
                        result = math_op.template operator()<i64, u64>(left_result, right_result, bin_expr->type, BinaryMathOpType::LEFT);
                    } else if((right_result.type == TokenType::VEC2 || right_result.type == TokenType::VEC3 || right_result.type == TokenType::VEC4) && (left_result.type == TokenType::FLOATCONSTANT || left_result.type == TokenType::DOUBLECONSTANT)) {
                        result = math_op.template operator()<f64, f64>(left_result, right_result, bin_expr->type, BinaryMathOpType::LEFT);
                    } else if((right_result.type == TokenType::DVEC2 || right_result.type == TokenType::DVEC3 || right_result.type == TokenType::DVEC4) && (left_result.type == TokenType::FLOATCONSTANT || left_result.type == TokenType::DOUBLECONSTANT)) {
                        result = math_op.template operator()<f64, f64>(left_result, right_result, bin_expr->type, BinaryMathOpType::LEFT);
                    } else {
                        INFO("left {}", static_cast<u32>(left_result.type));
                        INFO("right {}", static_cast<u32>(right_result.type));
                        throw std::runtime_error("unhandled math op"); 
                    }

                }

                return result;
            } else if(expr->get_type() == ExpressionType::ConstantValueExpression) {
                auto* cons_expr = dynamic_cast<ConstantValueExpression*>(expr);
                BinaryResult result;
                
                if(cons_expr->token.type == TokenType::FLOATCONSTANT) {
                    result.type = TokenType::FLOATCONSTANT;
                    result.data = std::vector<f64>{std::get<f64>(cons_expr->token.data)};
                } else if(cons_expr->token.type == TokenType::INTCONSTANT) {
                    result.type = TokenType::INTCONSTANT;
                    result.data = std::vector<i64>{std::get<i64>(cons_expr->token.data)};
                } else if(cons_expr->token.type == TokenType::UINTCONSTANT) {
                    result.type = TokenType::UINTCONSTANT;
                    result.data = std::vector<i64>{static_cast<i64>(std::get<u64>(cons_expr->token.data))};
                } else if(cons_expr->token.type == TokenType::DOUBLECONSTANT) {
                    result.type = TokenType::DOUBLECONSTANT;
                    result.data = std::vector<f64>{std::get<f64>(cons_expr->token.data)};
                } else {
                    throw std::runtime_error("unhandled type");
                }

                return result;
            } else if(expr->get_type() == ExpressionType::ConstructorExpression) {
                auto* cons_expr = dynamic_cast<ConstructorExpression*>(expr);
                BinaryResult result;
                result.type = cons_expr->type.type;
                std::vector<i64> ints = {};
                std::vector<f64> floats = {};

                for(auto& constant : cons_expr->values) {
                    if(constant->get_type() == ExpressionType::ConstantValueExpression) {
                        auto* constant_expr = dynamic_cast<ConstantValueExpression*>(constant.get());
                        switch(result.type) {
                            case TokenType::IVEC2 ... TokenType::IVEC4: { 
                                ints.push_back(std::get<i64>(constant_expr->token.data));
                                break;
                            }

                            case TokenType::UVEC2 ... TokenType::UVEC4: { 
                                ints.push_back(static_cast<i64>(std::get<u64>(constant_expr->token.data)));
                                break;
                            }

                            case TokenType::VEC2 ... TokenType::VEC4: { 
                                floats.push_back(std::get<f64>(constant_expr->token.data));
                                break;
                            }

                            case TokenType::DVEC2 ... TokenType::DVEC4: { 
                                floats.push_back(std::get<f64>(constant_expr->token.data));
                                break;
                            }

                            default: { throw std::runtime_error("hmmmmm"); }
                        }
                    } else {
                        throw std::runtime_error("unhandled type");
                    }
                }

                switch (result.type) {
                    case TokenType::IVEC2 ... TokenType::UVEC4: { result.data = ints; break; }
                    case TokenType::VEC2 ... TokenType::VEC4:   { result.data = floats; break; }
                    case TokenType::DVEC2 ... TokenType::DVEC4: { result.data = floats; break; }
                    default: { throw std::runtime_error("unhandled type"); }
                }

                return result;
            } else {
                throw std::runtime_error("unhandled type");
            }

            return {
                .type = TokenType::EOS,
                .data = std::monostate{}
            };
        };

        /*using binary_result = std::variant<std::monostate, f32, i32, u32, f64>;
        std::function<Token(Expression* expr)> visit_binary_expression;
        visit_binary_expression = [&visit_binary_expression](Expression* expr) -> Token {
            if(expr->get_type() == ExpressionType::BinaryExpression) {
                auto* bin_expr = dynamic_cast<BinaryExpression*>(expr);

                Token left_result = visit_binary_expression(bin_expr->left.get());
                Token right_result = visit_binary_expression(bin_expr->right.get());

                if(!std::holds_alternative<std::monostate>(left_result.data) && !std::holds_alternative<std::monostate>(right_result.data)) {
                    if(left_result.data.index() == right_result.data.index()) {
                        if(std::holds_alternative<f64>(left_result.data)) {
                            f64 a = std::get<f64>(left_result.data);
                            f64 b = std::get<f64>(right_result.data);
                            Token result;
                            result.type = left_result.type;

                            switch(bin_expr->type) {
                                case BinaryType::Multiply: { result.data = a * b; break; }
                                case BinaryType::Divide:   { result.data = a / b; break; }
                                case BinaryType::Add:      { result.data = a + b; break; }
                                case BinaryType::Subtract: { result.data = a - b; break; }
                                default: { throw std::runtime_error("unhandled binary operation"); }
                            }

                            return result;
                        } else if(std::holds_alternative<i64>(left_result.data)) {
                            i64 a = std::get<i64>(left_result.data);
                            i64 b = std::get<i64>(right_result.data);
                            Token result;
                            result.type = left_result.type;

                            switch(bin_expr->type) {
                                case BinaryType::Multiply: { result.data = a * b; break; }
                                case BinaryType::Divide:   { result.data = a / b; break; }
                                case BinaryType::Add:      { result.data = a + b; break; }
                                case BinaryType::Subtract: { result.data = a - b; break; }
                                default: { throw std::runtime_error("unhandled binary operation"); }
                            }

                            return result;
                        } else if(std::holds_alternative<u64>(left_result.data)) {
                            u64 a = std::get<u64>(left_result.data);
                            u64 b = std::get<u64>(right_result.data);
                            Token result;
                            result.type = left_result.type;

                            switch(bin_expr->type) {
                                case BinaryType::Multiply: { result.data = a * b; break; }
                                case BinaryType::Divide:   { result.data = a / b; break; }
                                case BinaryType::Add:      { result.data = a + b; break; }
                                case BinaryType::Subtract: { result.data = a - b; break; }
                                default: { throw std::runtime_error("unhandled binary operation"); }
                            }

                            return result;
                        }
                    } else {
                        throw std::runtime_error("not same type");
                    }
                } else {
                    throw std::runtime_error("hmmm");
                }
            } else if(expr->get_type() == ExpressionType::ConstantValueExpression) {
                auto* cons_expr = dynamic_cast<ConstantValueExpression*>(expr);
                if(cons_expr->token.type == TokenType::FLOATCONSTANT) {
                    return Token {
                        .type = TokenType::FLOATCONSTANT,
                        .data = std::get<f64>(cons_expr->token.data)
                    };
                } else if(cons_expr->token.type == TokenType::INTCONSTANT) {
                    return Token {
                        .type = TokenType::INTCONSTANT,
                        .data = std::get<i64>(cons_expr->token.data)
                    };
                } else if(cons_expr->token.type == TokenType::UINTCONSTANT) {
                    return Token {
                        .type = TokenType::UINTCONSTANT,
                        .data = std::get<u64>(cons_expr->token.data)
                    };
                } else if(cons_expr->token.type == TokenType::DOUBLECONSTANT) {
                    return Token {
                        .type = TokenType::DOUBLECONSTANT,
                        .data = std::get<f64>(cons_expr->token.data)
                    };
                }
            } else if(expr->get_type() == ExpressionType::ConstructorExpression) {
                auto* cons_expr = dynamic_cast<ConstructorExpression*>(expr);
                for(auto& con : cons_expr->values) {
                    visit_binary_expression(con.get());
                }
            }

            return Token { .type = TokenType::EOS, .data = std::monostate{} };
        };*/

        auto convert_value_into_bits = [](Token token) -> std::pair<TokenType, u32> {
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
        find_or_register_constant = [&](const std::unique_ptr<Expression>& expr) -> u32 {
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
            } /*else if(expr->get_type() == ExpressionType::BinaryExpression) {
                auto* e = dynamic_cast<BinaryExpression*>(expr.get());
                //type = e->token.type;
                auto pair = convert_value_into_bits(visit_binary_expression(expr.get()));
                type = pair.first;
                values.push_back(pair.second);
            }*/ 
            else if(expr->get_type() == ExpressionType::BinaryExpression) {
                auto* e = dynamic_cast<BinaryExpression*>(expr.get());
                BinaryResult result = look_binary_expression(expr.get());
                type = result.type;

                switch (result.type) {
                    case TokenType::FLOATCONSTANT: {
                        std::vector<f64>& data = std::get<std::vector<f64>>(result.data);
                        for(auto& value : data) {
                            auto pair = convert_value_into_bits({ .type = TokenType::FLOATCONSTANT, .data = value });
                            type = pair.first;
                            values.push_back(pair.second);
                        }
                        break;                       
                    }

                    case TokenType::INTCONSTANT: {
                        std::vector<i64>& data = std::get<std::vector<i64>>(result.data);
                        for(auto& value : data) {
                            auto pair = convert_value_into_bits({ .type = TokenType::INTCONSTANT, .data = value });
                            type = pair.first;
                            values.push_back(pair.second);
                        }
                        break;                       
                    }

                    case TokenType::UINTCONSTANT: {
                        std::vector<i64>& data = std::get<std::vector<i64>>(result.data);
                        for(auto& value : data) {
                            auto pair = convert_value_into_bits({ .type = TokenType::UINTCONSTANT, .data = static_cast<u64>(value) });
                            type = pair.first;
                            values.push_back(pair.second);
                        }
                        break;                       
                    }

                    case TokenType::DOUBLECONSTANT: {
                        std::vector<f64>& data = std::get<std::vector<f64>>(result.data);
                        for(auto& value : data) {
                            auto pair = convert_value_into_bits({ .type = TokenType::DOUBLECONSTANT, .data = value });
                            type = pair.first;
                            values.push_back(pair.second);
                        }
                        break;                       
                    }

                    case TokenType::IVEC2 ... TokenType::IVEC4: { 
                        std::vector<i64>& data = std::get<std::vector<i64>>(result.data);
                        for(auto& value : data) {
                            auto pair = convert_value_into_bits({ .type = TokenType::INTCONSTANT, .data = value });
                            values.push_back(pair.second);
                        }
                        break; 
                    }
                    case TokenType::UVEC2 ... TokenType::UVEC4: { 
                        std::vector<i64>& data = std::get<std::vector<i64>>(result.data);
                        for(auto& value : data) {
                            auto pair = convert_value_into_bits({ .type = TokenType::UINTCONSTANT, .data = static_cast<u64>(value) });
                            values.push_back(pair.second);
                        }
                        break; 
                    }
                    case TokenType::VEC2 ... TokenType::VEC4:   { 
                        std::vector<f64>& data = std::get<std::vector<f64>>(result.data);
                        for(auto& value : data) {
                            //INFO("tfftu {}", value);
                            auto pair = convert_value_into_bits({ .type = TokenType::FLOATCONSTANT, .data = value });
                            values.push_back(pair.second);
                        }
                        break; 
                    }
                    case TokenType::DVEC2 ... TokenType::DVEC4: { 
                        std::vector<f64>& data = std::get<std::vector<f64>>(result.data);
                        for(auto& value : data) {
                            auto pair = convert_value_into_bits({ .type = TokenType::DOUBLECONSTANT, .data = value });
                            values.push_back(pair.second);
                        }
                        break; 
                    }
                    default: { throw std::runtime_error("unhandled type"); }
                }

                /*for(auto& value : e->values) {
                    auto* v = dynamic_cast<ConstantValueExpression*>(value.get());
                    values.push_back(convert_value_into_bits(v->token).second);
                }*/
            }

            else {
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

            u32 id = 0;
            if(expr->get_type() == ExpressionType::ConstantValueExpression) {
                id = spirv.register_new_id();
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

                id = spirv.register_new_id();

                std::vector<u32> ids = {};
                for(auto& v : e->values) {
                    ids.push_back(find_or_register_constant(v));
                }

                switch(type) {
                    case TokenType::BVEC2 ... TokenType::VEC4:{
                        u32 type_id = find_or_register_type({ .type = type }, false);
                        spirv.OpConstantComposite(type_id, id, ids);
                        break;
                    } 
                    
                    case TokenType::DVEC2 ... TokenType::DVEC4:{
                        u32 type_id = find_or_register_type({ .type = type }, false);
                        spirv.OpConstantComposite(type_id, id, ids);
                        break;
                    } default: {
                        throw std::runtime_error("unhandled type");
                    }
                }
            } else if(expr->get_type() == ExpressionType::BinaryExpression) {
                //INFO("{}", static_cast<u32>(type));
                u32 type_id = find_or_register_type({ .type = type }, false);

                if(TokenType::FLOAT >= type && type <= TokenType::DOUBLE) {
                    //INFO("THIS");
                    id = spirv.register_new_id();
                    spirv.OpConstant(type_id, id, values);
                } else if((TokenType::BVEC2 >= type && type <= TokenType::VEC4) || (TokenType::DVEC2 >= type && type <= TokenType::DVEC4)) {
                    //INFO("THIS?");
                    u32 type_id = find_or_register_type({ .type = type }, false);
                    std::vector<u32> ids = {};
                    for(auto& value : values) {
                        bool found = false;
                        for(auto& spv_constant : spv_constants) {
                            if(spv_constant.type == type) {
                                if(value == spv_constant.values[0]) {
                                    ids.push_back(spv_constant.id);
                                    found = true;
                                    break;
                                }
                            }
                        }

                        if(!found) {
                            //INFO("here");
                            u32 constant_id = spirv.register_new_id();

                            TokenType constant_type = TokenType::EOS;

                            switch(type) {
                                case TokenType::IVEC2 ... TokenType::IVEC4: { constant_type = TokenType::INT; break; }
                                case TokenType::UVEC2 ... TokenType::UVEC4: { constant_type = TokenType::UINT; break; }
                                case TokenType::VEC2  ... TokenType::VEC4:   { constant_type = TokenType::FLOAT; break; }
                                case TokenType::DVEC2 ... TokenType::DVEC4: { constant_type = TokenType::FLOAT; break; }
                                default: { throw std::runtime_error("bzozo"); }
                            }

                            //INFO("bruh {}", static_cast<u32>(constant_type));

                            u32 constant_type_id = find_or_register_type(Token { .type = constant_type }, false);
                            spirv.OpConstant(constant_type_id, constant_id, { value });

                            spv_constants.push_back({
                                .type = type,
                                .values = { value },
                                .uuids = { 0 },
                                .id = constant_id,
                            });

                            ids.push_back(constant_id);
                        }
                    }

                    /*INFO("VALUES: {}", values.size());
                    for(auto& v : values) {
                        INFO("v {}", v);
                    }

                    INFO("IDS: {}", ids.size());
                    for(auto& _id : ids) {
                        INFO("id {}", _id);
                    }*/

                    id = spirv.register_new_id();
                    spirv.OpConstantComposite(type_id, id, ids);
                }
                else {
                    throw std::runtime_error("wrong type of value");
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
                    } else if(st->get_type() == StatementType::DeclareVariableStatement) {
                        auto* dc_stmt = dynamic_cast<DeclareVariableStatement*>(st.get());

                        if(dc_stmt->expression->get_type() == ExpressionType::ConstantValueExpression) {
                            u32 constant_id = find_or_register_constant(dc_stmt->expression);
                        } else if(dc_stmt->expression->get_type() == ExpressionType::ConstructorExpression) {
                            u32 constant_id = find_or_register_constant(dc_stmt->expression);
                        } else if(dc_stmt->expression->get_type() == ExpressionType::BinaryExpression) {
                            u32 constant_id = find_or_register_constant(dc_stmt->expression);
                            /*INFO("DWADWADWA");

                            Token result = visit_binary_expression(dc_stmt->expression.get());
                            INFO("{}", std::get<i64>(result.data));*/

                            //auto* bin_expr = dynamic_cast<BinaryExpression*>(dc_stmt->expression.get());
                            /*auto* left_expr = dynamic_cast<ConstantValueExpression*>(bin_expr->left.get());
                            auto* right_expr = dynamic_cast<ConstantValueExpression*>(bin_expr->right.get());
                            INFO("{}", std::get<i64>(left_expr->token.data));
                            INFO("{}", std::get<i64>(right_expr->token.data));*/

                            /*if(bin_expr->left->get_type() == ExpressionType::ConstantValueExpression) {
                                auto* left_expr = dynamic_cast<ConstantValueExpression*>(bin_expr->left.get());
                                INFO("{}", std::get<i64>(left_expr->token.data));
                            } else if(bin_expr->left->get_type() == ExpressionType::BinaryExpression) {
                                
                                auto* _bin_expr = dynamic_cast<BinaryExpression*>(bin_expr->left.get());
                                //INFO("{}", std::get<i64>(left_expr->token.data));

                                if(_bin_expr->left->get_type() == ExpressionType::ConstantValueExpression) {
                                    auto* left_expr = dynamic_cast<ConstantValueExpression*>(_bin_expr->left.get());
                                    INFO("{}", std::get<i64>(left_expr->token.data));

                                    auto* right_expr = dynamic_cast<ConstantValueExpression*>(_bin_expr->right.get());
                                    INFO("{}", std::get<i64>(right_expr->token.data));
                                }
                                

                            }

                            if(bin_expr->right->get_type() == ExpressionType::ConstantValueExpression) {
                                auto* right_expr = dynamic_cast<ConstantValueExpression*>(bin_expr->right.get());
                                INFO("{}", std::get<i64>(right_expr->token.data));
                            } else if(bin_expr->right->get_type() == ExpressionType::BinaryExpression) {
                                auto* _bin_expr = dynamic_cast<BinaryExpression*>(bin_expr->right.get());
                                //INFO("{}", std::get<i64>(left_expr->token.data));

                                if(_bin_expr->right->get_type() == ExpressionType::ConstantValueExpression) {
                                    auto* left_expr = dynamic_cast<ConstantValueExpression*>(_bin_expr->left.get());
                                    INFO("{}", std::get<i64>(left_expr->token.data));

                                    auto* right_expr = dynamic_cast<ConstantValueExpression*>(_bin_expr->right.get());
                                    INFO("{}", std::get<i64>(right_expr->token.data));
                                }
                            }*/
                        }
                    } else if(st->get_type() == StatementType::ReturnStatement){
                        auto* rt_stmt = dynamic_cast<ReturnStatement*>(st.get());

                        if(rt_stmt->expr->get_type() == ExpressionType::ConstantValueExpression) {
                            u32 constant_id = find_or_register_constant(rt_stmt->expr);
                        } else if(rt_stmt->expr->get_type() == ExpressionType::ConstructorExpression) {
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
                u32 name_id = find_or_register_name(fn_stmt->name);

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

                        u32 id = find_or_register_name(dc_stmt->name);

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

                            u32 id = find_or_register_name(std::get<std::string_view>(left_expr->token.data));

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

                                    u32 loaded_type_id = find_or_register_type({ .type = loaded_type }, false);

                                    u32 temp_id = spirv.register_new_id();
                                    spirv.OpLoad(loaded_type_id, temp_id, loaded_id);
                                    spirv.OpStore(id, temp_id);
                                } else {
                                    u32 value_id = find_or_register_constant(assign_expr->right);
                                    spirv.OpStore(id, value_id);
                                }
                            }
                        }
                    }  else if(st->get_type() == StatementType::DeclareVariableStatement) {
                        auto* dc_stmt = dynamic_cast<DeclareVariableStatement*>(st.get());

                        u32 id = find_or_register_name(dc_stmt->name);

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

                                u32 loaded_type_id = find_or_register_type({ .type = loaded_type }, false);

                                u32 temp_id = spirv.register_new_id();
                                spirv.OpLoad(loaded_type_id, temp_id, loaded_id);
                                spirv.OpStore(id, temp_id);
                            } else {
                                u32 value_id = find_or_register_constant(dc_stmt->expression);
                                spirv.OpStore(id, value_id);
                            }
                        } else if(dc_stmt->expression->get_type() == ExpressionType::CallFunctionExpression) {
                            auto* cfn_expr = dynamic_cast<CallFunctionExpression*>(dc_stmt->expression.get());
                            auto* cons_expr = dynamic_cast<ConstantValueExpression*>(cfn_expr->function_expr.get());

                            u32 function_id = find_or_register_name(std::get<std::string_view>(cons_expr->token.data));

                            u32 type_id = find_or_register_type(Token { .type = dc_stmt->type.type}, false);
                            
                            u32 result_id = spirv.register_new_id();
                            spirv.OpFunctionCall(type_id, result_id, function_id);   
                            spirv.OpStore(id, result_id);
                        
                        } else if(dc_stmt->expression->get_type() == ExpressionType::BinaryExpression) {
                            u32 value_id = find_or_register_constant(dc_stmt->expression);
                            spirv.OpStore(id, value_id);
                        }
                    } else if(st->get_type() == StatementType::ReturnStatement){
                        auto* rt_stmt = dynamic_cast<ReturnStatement*>(st.get());
                        if(rt_stmt->expr->get_type() == ExpressionType::ConstantValueExpression) {
                            u32 value_id = find_or_register_constant(rt_stmt->expr);

                            spirv.OpReturnValue(value_id);
                        } else if(rt_stmt->expr->get_type() == ExpressionType::ConstructorExpression) {
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


        std::string spirv_disassmble = {};

        core.Disassemble(spirv.data, &spirv_disassmble);

        std::cout << spirv_disassmble << std::endl;
        core.Validate(spirv.data);

        //throw std::runtime_error("bruh");

        /*std::ofstream file;
        file.open("shader.bin", std::ios::binary | std::ios::out);
        file.write(reinterpret_cast<char*>(spirv.data.data()), spirv.data.size() * sizeof(uint32_t));
        file.close();*/

        return spirv.data;
    }
}