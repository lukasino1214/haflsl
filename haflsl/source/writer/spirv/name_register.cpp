#include <haflsl/writer/spirv/name_register.hpp>
#include <stdexcept>

namespace haflsl {
    NameRegister::NameRegister(const std::vector<StatementPtr> &ast, const std::vector<SpvName>& spv_names) {
        for(auto& name : spv_names) {
            names.insert({name.name, name.id});
            spirv.OpName(name.id, name.name);
        }

        for(auto& stmt : ast) {
            stmt->visit(*this);
        }
    }

    void NameRegister::visit(ConstantValueExpression &node) {

    }

    void NameRegister::visit(BinaryExpression &node) {

    }

    void NameRegister::visit(UnaryExpression &node) {

    }

    void NameRegister::visit(IdentifierExpression &node) {

    }

    void NameRegister::visit(AccessIdentifierExpression &node) {

    }

    void NameRegister::visit(AccessIndexExpression &node) {

    }

    void NameRegister::visit(AssignExpression &node) {

    }

    void NameRegister::visit(CallFunctionExpression &node) {

    }

    void NameRegister::visit(ConstructorExpression &node) {

    }

    void NameRegister::visit(BreakStatement &node) {

    }

    void NameRegister::visit(ContinueStatement &node) {

    }

    void NameRegister::visit(DiscardStatement &node) {

    }

    void NameRegister::visit(ReturnStatement &node) {

    }

    void NameRegister::visit(DeclareFunctionStatement &node) {

    }

    void NameRegister::visit(DeclareStructStatement &node) {

    }

    void NameRegister::visit(DeclareVariableStatement &node) {

    }

    void NameRegister::visit(MultiStatement &node) {

    }

    void NameRegister::visit(ScopedStatement &node) {

    }

    void NameRegister::visit(BranchStatement &node) {

    }

    void NameRegister::visit(WhileStatement &node) {

    }

    void NameRegister::visit(ForStatement &node) {

    }

    void NameRegister::visit(ExpressionStatement &node) {

    }

    void NameRegister::visit(LocationStatement& node) {

    }

    void NameRegister::visit(PrintStatement &node) {

    }

    void NameRegister::register_name(const Token& token) {
        if(token.type == TokenType::IDENTIFIER) {
            register_name(std::get<Name>(token.value));
        } else {
            throw std::runtime_error("error in register name");
        }
    }

    void NameRegister::register_name(const Name& name) {
        if(names.find(name) == names.end()) {
            ID id = spirv.register_new_id();
            names.insert({name, id});

            spirv.OpName(id, name);
        }
    }
}