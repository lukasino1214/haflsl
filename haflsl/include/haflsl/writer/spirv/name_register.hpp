#pragma once

#include <haflsl/visitor.hpp>
#include <haflsl/writer/spirv/code_buffer.hpp>
#include <unordered_map>

namespace haflsl {
    using Name = std::string;
    using ID = u32;

    struct SpvName {
        Name name = {};
        ID id = {};
    };

    struct NameRegister : public ExpressionVisitor, public StatementVisitor {
        NameRegister(const std::vector<StatementPtr> &ast, const std::vector<SpvName>& spv_names);
        ~NameRegister() override = default;

        void visit(ConstantValueExpression &node) override;
        void visit(BinaryExpression &node) override;
        void visit(UnaryExpression &node) override;
        void visit(IdentifierExpression &node) override;
        void visit(AccessIdentifierExpression &node) override;
        void visit(AccessIndexExpression &node) override;
        void visit(AssignExpression &node) override;
        void visit(CallFunctionExpression &node) override;
        void visit(ConstructorExpression &node) override;

        void visit(BreakStatement &node) override;
        void visit(ContinueStatement &node) override;
        void visit(DiscardStatement &node) override;
        void visit(ReturnStatement &node) override;
        void visit(DeclareFunctionStatement &node) override;
        void visit(DeclareStructStatement &node) override;
        void visit(DeclareVariableStatement &node) override;
        void visit(MultiStatement &node) override;
        void visit(ScopedStatement &node) override;
        void visit(BranchStatement &node) override;
        void visit(WhileStatement &node) override;
        void visit(ForStatement &node) override;
        void visit(ExpressionStatement &node) override;
        void visit(LocationStatement& node) override;
        void visit(PrintStatement &node) override;

        void register_name(const Token& token);
        void register_name(const Name& name);

        std::unordered_map<Name, ID> names;

        CodeBuffer spirv;
    };
}