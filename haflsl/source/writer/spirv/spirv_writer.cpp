#include "haflsl/nodes.hpp"
#include "haflsl/result.hpp"
#include "haflsl/writer/spirv/code_buffer.hpp"
#include "haflsl/writer/spirv/constant_register.hpp"
#include "haflsl/writer/spirv/variable_register.hpp"
#include <haflsl/writer/spirv/spirv_writer.hpp>

#include <iostream>
#include <memory>
#include <stdexcept>
#include <string_view>

namespace haflsl {
    SpirvWriter::SpirvWriter() {}
    SpirvWriter::~SpirvWriter() {}

    auto SpirvWriter::compile(const std::vector<StatementPtr> &ast) -> Result<SPIRV> {
        spirv = std::make_unique<CodeBuffer>();

        spirv->data.emplace_back(0x07230203); // magic number stolen
        spirv->data.emplace_back(0x00010300);
        spirv->data.emplace_back(524298);     // stolen too
        spirv->data.emplace_back(0);          // <-- current_id + 1
        spirv->data.emplace_back(0x00000000); // reserved

        spirv->OpCapability(ECapability::Shader);
        spirv->OpExtInstImport(spirv->register_new_id(), "GLSL.std.450");
        spirv->OpMemoryModel(EAddressingModel::Logical, EMemoryModel::GLSL450);

        std::string entrypoint_name = "main";

        std::vector<SpvName> spv_names = {};

        auto find_or_register_name = [&](const std::string_view &name) -> u32 {
            for (auto &spv_name : spv_names) {
                if (spv_name.name == name) {
                    return spv_name.id;
                }
            }

            throw std::runtime_error("name wasnt registered");

            return 0;
        };

        for (const auto &statement : ast) {
            if (statement->get_type() == StatementType::DeclareFunctionStatement) {
                DeclareFunctionStatement *stmt = dynamic_cast<DeclareFunctionStatement *>(statement.get());

                if (stmt->name == entrypoint_name) {
                    spv_names.push_back({.name = entrypoint_name,
                                         .id = spirv->register_new_id()});
                }
            }
        }

        if (spv_names.empty()) {
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

        for (const auto &statement : ast) {
            if (statement->get_type() == StatementType::LocationStatement) {
                LocationStatement *stmt = dynamic_cast<LocationStatement *>(statement.get());

                u32 id = spirv->register_new_id();

                spv_names.push_back({.name = stmt->name,
                                     .id = id});

                spv_interfaces.push_back({.location = stmt->location,
                                          .way = (stmt->way.type == TokenType::IN) ? Way::IN : Way::OUT,
                                          .type = stmt->type.type,
                                          .name = stmt->name,
                                          .id = id});
            }
        }

        auto &entrypoint = spv_names[0];

        {
            std::vector<u32> interfaces_id = {};
            interfaces_id.reserve(spv_interfaces.size() * sizeof(u32));

            for (auto interface : spv_interfaces) {
                interfaces_id.push_back(interface.id);
            }

            spirv->OpEntryPoint(EExecutionModel::Fragment, entrypoint.id, entrypoint.name, interfaces_id);
        }

        spirv->OpExecutionMode(entrypoint.id, EExecutionMode::OriginUpperLeft);
        spirv->OpSource(ESourceLanguage::GLSL, 460, 0, "");

        {
            NameRegister reg(ast, spv_names);
            reg.spirv.current_id = spirv->current_id;
            for (const auto &stmt : ast) {
                stmt->visit(reg);
            }

            spirv->data.insert(spirv->data.end(), reg.spirv.data.begin(), reg.spirv.data.end());
            spirv->current_id = reg.spirv.current_id;
            names = reg.names;
        }

        for (auto &interface : spv_interfaces) {
            spirv->OpDecorate(interface.id, EDecoration::Location);
            spirv->data.push_back(interface.location);
        }

        {
            TypeRegister reg;
            reg.spirv.current_id = spirv->current_id;
            for (const auto &stmt : ast) {
                stmt->visit(reg);
            }

            spirv->data.insert(spirv->data.end(), reg.spirv.data.begin(), reg.spirv.data.end());
            spirv->current_id = reg.spirv.current_id;
            types = reg.types;
        }

        {
            VariableRegister reg(types, names);
            reg.spirv.current_id = spirv->current_id;
            for (const auto &stmt : ast) {
                stmt->visit(reg);
            }

            spirv->data.insert(spirv->data.end(), reg.spirv.data.begin(), reg.spirv.data.end());
            spirv->current_id = reg.spirv.current_id;
            pointers = reg.pointers;
            variables = reg.variables;
        }

        {
            ConstantRegister reg(types);
            reg.spirv.current_id = spirv->current_id;
            for (const auto &stmt : ast) {
                stmt->visit(reg);
            }

            spirv->data.insert(spirv->data.end(), reg.spirv.data.begin(), reg.spirv.data.end());
            spirv->current_id = reg.spirv.current_id;
            constants = reg.constants;
        }

        for (auto &stmt : ast) {
            stmt->visit(*this);
        }

        spirv->data[3] = spirv->current_id + 1;

        return Result<SPIRV>(spirv->data);
    }

    void SpirvWriter::visit(ConstantValueExpression &node) {
        expr_queue.push_back(node.get_type());

        if (node.token.type == TokenType::IDENTIFIER) {
            if (variables.find(std::get<std::string>(node.token.value)) != variables.end()) {
                object_id = variables.at(std::get<std::string>(node.token.value)).id;
            } else {
                throw std::runtime_error("couldnt not find a variable");
            }
        } else {
            if (expr_queue[expr_queue.size() - 1 - 1] == ExpressionType::ConstructorExpression) {
                u32 value = 0;
                switch (node.token.type) {
                    case TokenType::BOOL_CONSTANT: {
                        value = std::bit_cast<u32>(static_cast<u32>(std::get<bool>(node.token.value)));
                        break;
                    }
                    case TokenType::INT_CONSTANT: {
                        value = std::bit_cast<u32>(static_cast<i32>(std::get<i64>(node.token.value)));
                        break;
                    }
                    case TokenType::FLOAT_CONSTANT: {
                        value = std::bit_cast<u32>(static_cast<f32>(std::get<f64>(node.token.value)));
                        break;
                    }
                    default: {
                    }
                }

                TokenType type;
                switch(node.token.type) {
                    case TokenType::BOOL_CONSTANT: { type = TokenType::BOOL; break; }
                    case TokenType::INT_CONSTANT: { type = TokenType::INT; break; }
                    case TokenType::FLOAT_CONSTANT: { type = TokenType::FLOAT; break; }
                    default: {}
                }

                ID id;
                if(constants.find(SpvConstant {.type = type, .values = {value}}) != constants.end()) {
                    id = constants.at(SpvConstant {.type = type, .values = {value}});
                } else {
                    throw std::runtime_error("BRUHHH");
                }

                constructor_values.push_back(id);
            }
        }

        expr_queue.pop_back();
    }

    void SpirvWriter::visit(BinaryExpression &node) {
    }

    void SpirvWriter::visit(UnaryExpression &node) {
    }

    void SpirvWriter::visit(IdentifierExpression &node) {
    }

    void SpirvWriter::visit(AccessIdentifierExpression &node) {
    }

    void SpirvWriter::visit(AccessIndexExpression &node) {
    }

    void SpirvWriter::visit(AssignExpression &node) {
        expr_queue.push_back(node.get_type());
        node.left->visit(*this);
        node.right->visit(*this);

        if (node.left->get_type() == ExpressionType::ConstantValueExpression) {
            if (node.right->get_type() == ExpressionType::ConstructorExpression) {
                spirv->OpStore(object_id, constant_id);
            }
        }

        expr_queue.pop_back();
    }

    void SpirvWriter::visit(CallFunctionExpression &node) {
    }

    void SpirvWriter::visit(ConstructorExpression &node) {
        expr_queue.push_back(node.get_type());

        for(auto& expr : node.values) {
            expr->visit(*this);
        }

        if(constants.find(SpvConstant {.type = node.type.type, .values = constructor_values}) != constants.end()) {
            constant_id = constants.at(SpvConstant {.type = node.type.type, .values = constructor_values});
        }

        constructor_values.clear();

        expr_queue.pop_back();
    }

    void SpirvWriter::visit(BreakStatement &node) {
    }

    void SpirvWriter::visit(ContinueStatement &node) {
    }

    void SpirvWriter::visit(DiscardStatement &node) {
    }

    void SpirvWriter::visit(ReturnStatement &node) {
    }

    void SpirvWriter::visit(DeclareFunctionStatement &node) {
        stmt_queue.push_back(node.get_type());

        ID return_type_id = 0;
        if (types.find(SpvType{.type = node.returned_type.type, .function = false}) != types.end()) {
            return_type_id = types.at(SpvType{.type = node.returned_type.type, .function = false});
        }

        ID name_id = 0;
        if (names.find(node.name) != names.end()) {
            name_id = names.at(node.name);
        }

        ID function_type_id = 0;
        if (types.find(SpvType{.type = node.returned_type.type, .function = true}) != types.end()) {
            function_type_id = types.at(SpvType{.type = node.returned_type.type, .function = true});
        }

        spirv->OpFunction(return_type_id, name_id, EFunctionControl::None, function_type_id);
        spirv->OpLabel(spirv->register_new_id());

        for (auto &stmt : node.statements) {
            stmt->visit(*this);
        }

        if (node.returned_type.type == TokenType::VOID) {
            spirv->OpReturn();
        }
        spirv->OpFunctionEnd();

        stmt_queue.pop_back();
    }

    void SpirvWriter::visit(DeclareStructStatement &node) {
    }

    void SpirvWriter::visit(DeclareVariableStatement &node) {
    }

    void SpirvWriter::visit(MultiStatement &node) {
    }

    void SpirvWriter::visit(ScopedStatement &node) {
    }

    void SpirvWriter::visit(BranchStatement &node) {
    }

    void SpirvWriter::visit(WhileStatement &node) {
    }

    void SpirvWriter::visit(ForStatement &node) {
    }

    void SpirvWriter::visit(ExpressionStatement &node) {
        stmt_queue.push_back(node.get_type());
        node.expression->visit(*this);
        stmt_queue.pop_back();
    }

    void SpirvWriter::visit(LocationStatement &node) {
    }

    void SpirvWriter::visit(PrintStatement &node) {
    }
} // namespace haflsl