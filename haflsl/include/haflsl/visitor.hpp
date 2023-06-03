#pragma once

#include <haflsl/nodes.hpp>

namespace haflsl {
    struct ExpressionVisitor {
        ExpressionVisitor() = default;
        ExpressionVisitor(const ExpressionVisitor &) = delete;
        ExpressionVisitor(ExpressionVisitor &&) = delete;
        virtual ~ExpressionVisitor() = default;

        virtual void visit(ConstantValueExpression &node) = 0;
        virtual void visit(BinaryExpression &node) = 0;
        virtual void visit(UnaryExpression &node) = 0;
        virtual void visit(IdentifierExpression &node) = 0;
        virtual void visit(AccessIdentifierExpression &node) = 0;
        virtual void visit(AccessIndexExpression &node) = 0;
        virtual void visit(AssignExpression &node) = 0;
        virtual void visit(CallFunctionExpression &node) = 0;
        virtual void visit(ConstructorExpression &node) = 0;

        ExpressionVisitor &operator=(const ExpressionVisitor &) = delete;
        ExpressionVisitor &operator=(ExpressionVisitor &&) = delete;
    };

    struct StatementVisitor {
        StatementVisitor() = default;
        StatementVisitor(const StatementVisitor &) = delete;
        StatementVisitor(StatementVisitor &&) = delete;
        virtual ~StatementVisitor() = default;

        virtual void visit(BreakStatement &node) = 0;
        virtual void visit(ContinueStatement &node) = 0;
        virtual void visit(DiscardStatement &node) = 0;
        virtual void visit(ReturnStatement &node) = 0;
        virtual void visit(DeclareFunctionStatement &node) = 0;
        virtual void visit(DeclareStructStatement &node) = 0;
        virtual void visit(DeclareVariableStatement &node) = 0;
        virtual void visit(MultiStatement &node) = 0;
        virtual void visit(ScopedStatement &node) = 0;
        virtual void visit(BranchStatement &node) = 0;
        virtual void visit(WhileStatement &node) = 0;
        virtual void visit(ForStatement &node) = 0;
        virtual void visit(ExpressionStatement &node) = 0;
        virtual void visit(LocationStatement& node) = 0;
        virtual void visit(PrintStatement &node) = 0;

        StatementVisitor &operator=(const StatementVisitor &) = delete;
        StatementVisitor &operator=(StatementVisitor &&) = delete;
    };
} // namespace haflsl