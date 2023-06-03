#include "haflsl/token.hpp"
#include <haflsl/writer/spirv/type_register.hpp>
#include <iostream>

namespace haflsl {
    void TypeRegister::visit(ConstantValueExpression &node) {

    }

    void TypeRegister::visit(BinaryExpression &node) {

    }

    void TypeRegister::visit(UnaryExpression &node) {

    }

    void TypeRegister::visit(IdentifierExpression &node) {

    }

    void TypeRegister::visit(AccessIdentifierExpression &node) {

    }

    void TypeRegister::visit(AccessIndexExpression &node) {

    }

    void TypeRegister::visit(AssignExpression &node) {

    }

    void TypeRegister::visit(CallFunctionExpression &node) {

    }

    void TypeRegister::visit(ConstructorExpression &node) {

    }

    void TypeRegister::visit(BreakStatement &node) {

    }

    void TypeRegister::visit(ContinueStatement &node) {

    }

    void TypeRegister::visit(DiscardStatement &node) {

    }

    void TypeRegister::visit(ReturnStatement &node) {

    }

    void TypeRegister::visit(DeclareFunctionStatement &node) {
        register_type(node.returned_type.type, true);
    }

    void TypeRegister::visit(DeclareStructStatement &node) {

    }

    void TypeRegister::visit(DeclareVariableStatement &node) {

    }

    void TypeRegister::visit(MultiStatement &node) {

    }

    void TypeRegister::visit(ScopedStatement &node) {

    }

    void TypeRegister::visit(BranchStatement &node) {

    }

    void TypeRegister::visit(WhileStatement &node) {

    }

    void TypeRegister::visit(ForStatement &node) {

    }

    void TypeRegister::visit(ExpressionStatement &node) {

    }

    void TypeRegister::visit(LocationStatement &node) {
        register_type(node.type.type, false);
    }

    void TypeRegister::visit(PrintStatement &node) {

    }

    auto TypeRegister::register_type(TokenType type, bool fn) -> u32 {
        if (types.find(SpvType{.type = type, .function = fn}) == types.end()) {
            if (fn) {
                ID id = spirv.register_new_id();
                ID under_id = register_type(type, false);

                spirv.OpTypeFunction(id, under_id);

                types.insert({SpvType{.type = type, .function = true}, id});
                return id;
            }

            ID under_id = 0;

            if (type == TokenType::VEC2 || type == TokenType::VEC3 || type == TokenType::VEC4) {
                under_id = register_type(TokenType::FLOAT, false);
            }

            if (type == TokenType::IVEC2 || type == TokenType::IVEC3 || type == TokenType::IVEC4) {
                under_id = register_type(TokenType::INT, false);
            }

            ID id = spirv.register_new_id();

            switch (type) {
                case TokenType::VOID: {
                    spirv.OpTypeVoid(id);
                    break;
                }
                case TokenType::BOOL: {
                    spirv.OpTypeBool(id);
                    break;
                }
                case TokenType::INT: {
                    spirv.OpTypeInt(id, 32, 1);
                    break;
                }
                case TokenType::FLOAT: {
                    spirv.OpTypeFloat(id, 32);
                    break;
                }
                case TokenType::VEC2: {
                    spirv.OpTypeVector(id, under_id, 2);
                    break;
                }
                case TokenType::VEC3: {
                    spirv.OpTypeVector(id, under_id, 3);
                    break;
                }
                case TokenType::VEC4: {
                    spirv.OpTypeVector(id, under_id, 4);
                    break;
                }
                case TokenType::IVEC2: {
                    spirv.OpTypeVector(id, under_id, 2);
                    break;
                }
                case TokenType::IVEC3: {
                    spirv.OpTypeVector(id, under_id, 3);
                    break;
                }
                case TokenType::IVEC4: {
                    spirv.OpTypeVector(id, under_id, 4);
                    break;
                }
            }

            types.insert({SpvType{.type = type, .function = false}, id});
            return id;
        }

        return types.at(SpvType{.type = type, .function = fn});
    }

} // namespace haflsl