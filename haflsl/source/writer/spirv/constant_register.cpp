#include "haflsl/token.hpp"
#include <haflsl/writer/spirv/constant_register.hpp>
#include <stdexcept>
#include <bit>
#include <iostream>

namespace haflsl {
    ConstantRegister::ConstantRegister(const std::unordered_map<SpvType, ID, SpvTypeHash>& _types) : types{_types} {}

    void ConstantRegister::visit(ConstantValueExpression &node) {
        u32 value = 0;
        switch (node.token.type) {
            case TokenType::BOOL_CONSTANT: { value = std::bit_cast<u32>(static_cast<u32>(std::get<bool>(node.token.value))); break; }
            case TokenType::INT_CONSTANT: { value = std::bit_cast<u32>(static_cast<i32>(std::get<i64>(node.token.value))); break; }
            case TokenType::FLOAT_CONSTANT: { value = std::bit_cast<u32>(static_cast<f32>(std::get<f64>(node.token.value))); break; }
            default: {}
        }

        if(constructor) { constructor_values.push_back(value); }

        register_constant(node.token.type, {value});
    }

    void ConstantRegister::visit(BinaryExpression &node) {

    }

    void ConstantRegister::visit(UnaryExpression &node) {

    }

    void ConstantRegister::visit(IdentifierExpression &node) {

    }

    void ConstantRegister::visit(AccessIdentifierExpression &node) {

    }

    void ConstantRegister::visit(AccessIndexExpression &node) {

    }

    void ConstantRegister::visit(AssignExpression &node) {
        node.right->visit(*this);
    }

    void ConstantRegister::visit(CallFunctionExpression &node) {

    }

    void ConstantRegister::visit(ConstructorExpression &node) {
        if(constructor) { throw std::runtime_error("already has constructor"); }
        constructor = true;

        for(auto& v : node.values) {
            v->visit(*this);
        }

        register_constant(node.type.type, constructor_values);
        constructor_values.clear();
        constructor = false;
    }

    void ConstantRegister::visit(BreakStatement &node) {

    }

    void ConstantRegister::visit(ContinueStatement &node) {

    }

    void ConstantRegister::visit(DiscardStatement &node) {

    }

    void ConstantRegister::visit(ReturnStatement &node) {

    }

    void ConstantRegister::visit(DeclareFunctionStatement &node) {
        for(auto& v : node.statements) {
            v->visit(*this);
        }
    }

    void ConstantRegister::visit(DeclareStructStatement &node) {

    }

    void ConstantRegister::visit(DeclareVariableStatement &node) {

    }

    void ConstantRegister::visit(MultiStatement &node) {

    }

    void ConstantRegister::visit(ScopedStatement &node) {

    }

    void ConstantRegister::visit(BranchStatement &node) {

    }

    void ConstantRegister::visit(WhileStatement &node) {

    }

    void ConstantRegister::visit(ForStatement &node) {

    }

    void ConstantRegister::visit(ExpressionStatement &node) {
        node.expression->visit(*this);
    }

    void ConstantRegister::visit(LocationStatement& node) {

    }

    void ConstantRegister::visit(PrintStatement &node) {

    }
    
    auto ConstantRegister::register_constant(TokenType type, const std::vector<u32> &values) -> u32 {
        switch(type) {
            case TokenType::BOOL_CONSTANT: { type = TokenType::BOOL; break; }
            case TokenType::INT_CONSTANT: { type = TokenType::INT; break; }
            case TokenType::FLOAT_CONSTANT: { type = TokenType::FLOAT; break; }
            default: {}
        }

        if(constants.find(SpvConstant {.type = type, .values = values }) == constants.end()) {
            ID type_id = 0;
            if(types.find(SpvType{.type = type, .function = false}) != types.end()) {
                type_id = types.at(SpvType{.type = type, .function = false});
            } else { throw std::runtime_error("type couldnt be found in register constant"); }

            ID id = spirv.register_new_id();

            if(static_cast<u32>(type) >= static_cast<u32>(TokenType::BOOL) && static_cast<u32>(type) <= static_cast<u32>(TokenType::FLOAT)) {
                spirv.OpConstant(type_id, id, values);
                constants.insert({SpvConstant {.type = type, .values = values }, id});
            } else if(static_cast<u32>(type) >= static_cast<u32>(TokenType::VEC2) && static_cast<u32>(type) <= static_cast<u32>(TokenType::IVEC4)) {
                TokenType under_type = {};
                if(static_cast<u32>(type) >= static_cast<u32>(TokenType::VEC2) && static_cast<u32>(type) <= static_cast<u32>(TokenType::VEC4)) { under_type = TokenType::FLOAT; }
                if(static_cast<u32>(type) >= static_cast<u32>(TokenType::IVEC2) && static_cast<u32>(type) <= static_cast<u32>(TokenType::IVEC4)) { under_type = TokenType::INT; }
                
                std::vector<ID> ids = {};
                for(u32 v : values) {
                    ids.push_back(register_constant(under_type, {v}));
                }
                
                spirv.OpConstantComposite(type_id, id, ids);
                constants.insert({SpvConstant {.type = type, .values = ids }, id});
            } else {
                throw std::runtime_error("unhandled type in register constant");
            }

            return id;
        }
        
        return constants.at(SpvConstant {.type = type, .values = values });
    }
}