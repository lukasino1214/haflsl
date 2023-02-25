#include "haflsl/nodes.hpp"
#include "haflsl/token.hpp"
#include <haflsl/transpiler.hpp>
#include <haflsl/code_buffer.hpp>
#include <iostream>

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
        //spirv.OpName(4, "main");

        for(auto& name : spv_names) {
            spirv.OpName(name.id, name.name);
        }

        for(auto& interface : spv_interfaces) {
            //spirv.OpName(name.id, name.name);
            spirv.OpDecorate(interface.id, EDecoration::Location); spirv.data.push_back(interface.location);
        }

        struct SpvTypes {
            TokenType type = {};
            bool function = false;
            u32 id = {};
        };

        std::vector<SpvTypes> spv_types = {};

        for(auto& statement : ast.statements) {
            if(statement->get_type() == StatementType::DeclareFunctionStatement) {
                DeclareFunctionStatement* fn = dynamic_cast<DeclareFunctionStatement*>(statement.get());

                u32 type_id = 0;
                for(auto& type : spv_types) {
                    if(type.type == fn->returned_type.type) {
                        type_id = type.id;
                        break;
                    }
                }

                if(type_id == 0) {
                    type_id = spirv.register_new_id();
                    spv_types.push_back({
                        .type = fn->returned_type.type,
                        .function = false,
                        .id = type_id
                    });
                    
                    switch(fn->returned_type.type) {
                        case TokenType::FLOAT: {
                            spirv.OpTypeFloat(type_id, 32);
                            break;
                        }

                        case TokenType::VOID: {
                            spirv.OpTypeVoid(type_id);
                            break;
                        }
                    }
                }

                u32 fn_id = spirv.register_new_id();
                
                spv_types.push_back({
                    .type = fn->returned_type.type,
                    .function = true,
                    .id = fn_id
                });
                spirv.OpTypeFunction(fn_id, type_id);
            }

            if(statement->get_type() == StatementType::LocationStatement) {
                LocationStatement* stmt = dynamic_cast<LocationStatement*>(statement.get());

                u32 type_id = 0;
                for(auto& type : spv_types) {
                    if(type.type == stmt->type.type) {
                        type_id = type.id;
                        break;
                    }
                }

                if(type_id == 0) {
                    type_id = spirv.register_new_id();
                    spv_types.push_back({
                        .type = stmt->type.type,
                        .function = false,
                        .id = type_id
                    });
                    
                    switch(stmt->type.type) {
                        case TokenType::FLOAT: {
                            spirv.OpTypeFloat(type_id, 32);
                            break;
                        }

                        case TokenType::VOID: {
                            spirv.OpTypeVoid(type_id);
                            break;
                        }

                        case TokenType::VEC4: {
                            u32 component_type_id = 0;
                            for(auto& type : spv_types) {
                                if(type.type == TokenType::FLOAT) {
                                    type_id = type.id;
                                    break;
                                }
                            }

                            if(component_type_id == 0) {
                                component_type_id = spirv.register_new_id();
                                spv_types.push_back({
                                    .type = TokenType::FLOAT,
                                    .function = false,
                                    .id = component_type_id
                                });

                                spirv.OpTypeFloat(component_type_id, 32);
                            }

                            spirv.OpTypeVector(type_id, component_type_id, 4);
                            break;
                        }
                    }
                }
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

                    u32 type_id = 0;
                    for(auto& type : spv_types) {
                        if(type.type == stmt->type.type) {
                            type_id = type.id;
                            break;
                        }
                    }

                    spirv.OpTypePointer(id, EStorageClass::Output, type_id);
                }
            }
        }

        struct SpvVariable {
            EStorageClass storage_class = {};
            TokenType type = {};
            u32 id = {};
        };

        std::vector<SpvPointer> spv_variable = {};

        for(const auto& statement : ast.statements) {
            if(statement->get_type() == StatementType::LocationStatement) {
                LocationStatement* stmt = dynamic_cast<LocationStatement*>(statement.get());

                bool found = false;
                for(auto& pointer : spv_variable) {
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

                    spv_variable.push_back({
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

        struct SpvConstant {
            TokenType type = {};
            u32 value = {};
            u32 id = {};
        };

        std::vector<SpvConstant> spv_constants = {};

        for(auto& statement : ast.statements) {
            if(statement->get_type() == StatementType::DeclareFunctionStatement) {
                DeclareFunctionStatement* stmt = dynamic_cast<DeclareFunctionStatement*>(statement.get());

                for(auto& st : stmt->statements) {
                    if(st->get_type() == StatementType::ExpressionStatement) {
                        ExpressionStatement* expr_stmt = dynamic_cast<ExpressionStatement*>(st.get());
                        
                        if(expr_stmt->expression->get_type() == ExpressionType::AssignExpression) {
                            AssignExpression* assign_expr = dynamic_cast<AssignExpression*>(expr_stmt->expression.get());

                            if(assign_expr->right->get_type() == ExpressionType::ConstructorExpression) {
                                ConstructorExpression* cons_expr = dynamic_cast<ConstructorExpression*>(assign_expr->right.get());
                            
                                for(auto& constant : cons_expr->values) {
                                    if(constant->get_type() == ExpressionType::ConstantValueExpression) {
                                        ConstantValueExpression* constant_expr = dynamic_cast<ConstantValueExpression*>(constant.get());
                                    
                                        bool found = false;
                                        for(auto& con : spv_constants) {
                                            if(con.type == constant_expr->token.type && con.value == std::bit_cast<u32>(static_cast<f32>(std::get<f64>(constant_expr->token.data)))) {
                                                found = true;
                                            }
                                        }

                                        if(!found) {
                                            u32 id = spirv.register_new_id();
                                            u32 value = std::bit_cast<u32>(static_cast<f32>(std::get<f64>(constant_expr->token.data)));
                                            spv_constants.push_back({
                                                .type = constant_expr->token.type,
                                                .value = value,
                                                .id = id
                                            });

                                            u32 type_id = 0;
                                            for(auto& type : spv_types) {
                                                if(type.type == TokenType::FLOAT) {
                                                    type_id = type.id;
                                                    break;
                                                }
                                            }

                                            spirv.OpConstant(type_id, id, { value });
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        struct SpvConstantComposite {
            TokenType type = {};
            std::vector<u32> values = {};
            u32 id = {};
        };

        std::vector<SpvConstantComposite> spv_constant_composites = {};

        for(auto& statement : ast.statements) {
            if(statement->get_type() == StatementType::DeclareFunctionStatement) {
                DeclareFunctionStatement* stmt = dynamic_cast<DeclareFunctionStatement*>(statement.get());

                for(auto& st : stmt->statements) {
                    if(st->get_type() == StatementType::ExpressionStatement) {
                        ExpressionStatement* expr_stmt = dynamic_cast<ExpressionStatement*>(st.get());
                        
                        if(expr_stmt->expression->get_type() == ExpressionType::AssignExpression) {
                            AssignExpression* assign_expr = dynamic_cast<AssignExpression*>(expr_stmt->expression.get());

                            if(assign_expr->right->get_type() == ExpressionType::ConstructorExpression) {
                                ConstructorExpression* cons_expr = dynamic_cast<ConstructorExpression*>(assign_expr->right.get());
                            
                                if(cons_expr->type.type == TokenType::VEC4) {
                                    std::vector<u32> constants = {};

                                    for(auto& constant : cons_expr->values) {
                                        if(constant->get_type() == ExpressionType::ConstantValueExpression) {
                                            ConstantValueExpression* constant_expr = dynamic_cast<ConstantValueExpression*>(constant.get());
                                        
                                            for(auto bruh : spv_constants) {
                                                if(bruh.type == constant_expr->token.type && bruh.value == std::bit_cast<u32>(static_cast<f32>(std::get<f64>(constant_expr->token.data)))) {
                                                    constants.push_back(bruh.id);
                                                }
                                            }
                                        }
                                    }

                                    u32 id = spirv.register_new_id();
                                    spv_constant_composites.push_back({
                                        .type = cons_expr->type.type,
                                        .values = {},
                                        .id = id
                                    });

                                    u32 type_id = 0;
                                    for(auto& type : spv_types) {
                                        if(type.type == cons_expr->type.type) {
                                            type_id = type.id;
                                            break;
                                        }
                                    }

                                    //INFO("BRO {}", type_id);

                                    spirv.OpConstantComposite(type_id, id, constants);
                                }
                            }
                        }
                    }
                }
            }
        }

        for(auto& statement : ast.statements) {
            if(statement->get_type() == StatementType::DeclareFunctionStatement) {
                DeclareFunctionStatement* fn_stmt = dynamic_cast<DeclareFunctionStatement*>(statement.get());

                u32 return_type_id = 0;
                for(auto& type : spv_types) {
                    if(type.type == fn_stmt->returned_type.type && type.function == false) {
                        return_type_id = type.id;
                        break;
                    }
                }

                //INFO("{}", return_type_id);

                u32 function_type_id = 0;
                for(auto& type : spv_types) {
                    if(type.type == fn_stmt->returned_type.type && type.function == true) {
                        function_type_id = type.id;
                        break;
                    }
                }

                //INFO("{}", function_type_id);

                u32 name_id = 0;
                for(auto& name : spv_names) {
                    if(name.name == fn_stmt->name) {
                        name_id = name.id;
                        break;
                    }
                }

                //INFO("{}", name_id);

                spirv.OpFunction(return_type_id, name_id, EFunctionControl::None, function_type_id);
                spirv.OpLabel(spirv.register_new_id());

                for(auto& st : fn_stmt->statements) {
                    if(st->get_type() == StatementType::ExpressionStatement) {
                        ExpressionStatement* expr_stmt = dynamic_cast<ExpressionStatement*>(st.get());
                        
                        if(expr_stmt->expression->get_type() == ExpressionType::AssignExpression) {
                            AssignExpression* assign_expr = dynamic_cast<AssignExpression*>(expr_stmt->expression.get()); 

                            ConstantValueExpression* left_expr = dynamic_cast<ConstantValueExpression*>(assign_expr->left.get()); 

                            //INFO("{}", std::get<std::string_view>(left_expr->token.data));

                            u32 name_id = 0;
                            for(auto& name : spv_names) {
                                if(name.name == std::get<std::string_view>(left_expr->token.data)) {
                                    name_id = name.id;
                                    break;
                                }
                            }

                            //INFO("here");

                            spirv.OpStore(name_id, spv_constant_composites[0].id);
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