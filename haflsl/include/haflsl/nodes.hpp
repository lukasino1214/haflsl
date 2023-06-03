#pragma once

#include <memory>
#include <vector>

#include <haflsl/types.hpp>
#include <haflsl/token.hpp>

namespace haflsl {
    enum class ExpressionType : u32 {
        ConstantValueExpression,
        BinaryExpression,
        UnaryExpression,
        IdentifierExpression,
        AccessIdentifierExpression,
        AccessIndexExpression,
        AssignExpression,
        CallFunctionExpression,
        ConstructorExpression,
    };

    struct Expression;
    struct ExpressionVisitor;

    using ExpressionPtr = std::unique_ptr<Expression>;

    struct Expression {
        Expression() = default;
        Expression(const Expression &) = delete;
        Expression(Expression &&) noexcept = default;
        virtual ~Expression() = default;

        virtual auto get_type() -> ExpressionType = 0;
        virtual auto get_name() -> std::string_view = 0;

        virtual void visit(ExpressionVisitor &visitor) = 0;

        Expression &operator=(const Expression &) = delete;
        Expression &operator=(Expression &&) noexcept = default;
    };

    struct ConstantValueExpression : public Expression {
        auto get_type() -> ExpressionType override { return ExpressionType::ConstantValueExpression; }
        auto get_name() -> std::string_view override { return "ConstantValueExpression"; }

        void visit(ExpressionVisitor &visitor) override;

        Token token; // has type and data. thats why I have token here -_-
    };

    enum class BinaryType : u32 {
        Multiply,
        Divide,
        Modulo,
        Add,
        Subtract,
        BitShiftLeft,
        BitShiftRight,
        CompLt,
        CompGt,
        CompLe,
        CompGe,
        CompEq,
        CompNe,
        BitAnd,
        BitExOr,
        BitInOr,
        LogicalAnd,
        LogicalOr
    };

    struct BinaryExpression : public Expression {
        auto get_type() -> ExpressionType override { return ExpressionType::BinaryExpression; }
        auto get_name() -> std::string_view override { return "BinaryExpression"; }

        void visit(ExpressionVisitor &visitor) override;

        BinaryType type;
        ExpressionPtr left;
        ExpressionPtr right;
    };

    enum class UnaryType {
        LogicalNot,
        Minus,
        Plus
    };

    struct UnaryExpression : public Expression {
        auto get_type() -> ExpressionType override { return ExpressionType::UnaryExpression; }
        auto get_name() -> std::string_view override { return "UnaryExpression"; }

        void visit(ExpressionVisitor &visitor) override;

        UnaryType type;
        ExpressionPtr expr;
    };

    struct IdentifierExpression : public Expression {
        auto get_type() -> ExpressionType override { return ExpressionType::IdentifierExpression; }
        auto get_name() -> std::string_view override { return "IdentifierExpression"; }

        void visit(ExpressionVisitor &visitor) override;

        std::string name;
    };

    struct AccessIdentifierExpression : public Expression {
        auto get_type() -> ExpressionType override { return ExpressionType::AccessIdentifierExpression; }
        auto get_name() -> std::string_view override { return "AccessIdentifierExpression"; }

        void visit(ExpressionVisitor &visitor) override;

        std::vector<std::string> identifiers;
        ExpressionPtr expr;
    };

    struct AccessIndexExpression : public Expression {
        auto get_type() -> ExpressionType override { return ExpressionType::AccessIndexExpression; }
        auto get_name() -> std::string_view override { return "AccessIndexExpression"; }

        void visit(ExpressionVisitor &visitor) override;

        std::vector<ExpressionPtr> indices;
        ExpressionPtr expr;
    };

    enum class AssignType : u32 {
        Simple,
        CompoundAdd,
        CompoundSubtract,
        CompoundMultiply,
        CompoundDivide,
        CompoundModulo,
        CompoundBitShiftLeft,
        CompoundBitShiftRight,
        CompoundBitAnd,
        CompoundBitExOr,
        CompoundBitInOr
    };

    struct AssignExpression : public Expression {
        auto get_type() -> ExpressionType override { return ExpressionType::AssignExpression; }
        auto get_name() -> std::string_view override { return "AssignExpression"; }

        void visit(ExpressionVisitor &visitor) override;

        AssignType type;
        ExpressionPtr left;
        ExpressionPtr right;
    };

    struct CallFunctionExpression : public Expression {
        auto get_type() -> ExpressionType override { return ExpressionType::CallFunctionExpression; }
        auto get_name() -> std::string_view override { return "CallFunctionExpression"; }

        void visit(ExpressionVisitor &visitor) override;

        ExpressionPtr function_expr;
        std::vector<ExpressionPtr> parameters;
    };

    struct ConstructorExpression : public Expression {
        auto get_type() -> ExpressionType override { return ExpressionType::ConstructorExpression; }
        auto get_name() -> std::string_view override { return "ConstructorExpression"; }

        void visit(ExpressionVisitor &visitor) override;

        Token type;
        std::vector<ExpressionPtr> values;
    };

    enum class StatementType : u32 {
        BreakStatement = 0,
        ContinueStatement = 1,
        DiscardStatement = 2,
        ReturnStatement = 3,
        DeclareFunctionStatement = 4,
        DeclareStructStatement = 5,
        DeclareVariableStatement = 6,
        MultiStatement = 7,
        ScopedStatement = 8,
        BranchStatement = 9,
        WhileStatement = 10,
        ForStatement = 11,
        ExpressionStatement = 12,
        LocationStatement = 13,
        PrintStatement = 14
    };

    struct Statement;
    struct StatementVisitor;

    using StatementPtr = std::unique_ptr<Statement>;

    struct Statement {
        Statement() = default;
        Statement(const Statement &) = delete;
        Statement(Statement &&) noexcept = default;
        virtual ~Statement() = default;

        virtual auto get_type() -> StatementType = 0;
        virtual auto get_name() -> std::string_view = 0;

        virtual void visit(StatementVisitor &visitor) = 0;

        Statement &operator=(const Statement &) = delete;
        Statement &operator=(Statement &&) noexcept = default;
    };

    struct StructMember {
        Token token;
        std::string_view name;
    };

    struct DeclareStructStatement : public Statement {
        auto get_type() -> StatementType override { return StatementType::DeclareStructStatement; }
        auto get_name() -> std::string_view override { return "DeclareStructStatement"; }

        void visit(StatementVisitor &visitor) override;

        std::string name;
        std::vector<StructMember> members;
        std::vector<StatementPtr> methods;
    };

    struct Parameter {
        Token token;
        std::string name;
    };

    struct DeclareFunctionStatement : public Statement {
        auto get_type() -> StatementType override { return StatementType::DeclareFunctionStatement; }
        auto get_name() -> std::string_view override { return "DeclareFunctionStatement"; }

        void visit(StatementVisitor &visitor) override;

        std::string name;
        Token returned_type;
        std::vector<Parameter> parameters;
        std::vector<StatementPtr> statements;
    };

    struct BreakStatement : public Statement {
        auto get_type() -> StatementType override { return StatementType::BreakStatement; }
        auto get_name() -> std::string_view override { return "BreakStatement"; }

        void visit(StatementVisitor &visitor) override;
    };

    struct ContinueStatement : public Statement {
        auto get_type() -> StatementType override { return StatementType::ContinueStatement; }
        auto get_name() -> std::string_view override { return "ContinueStatement"; }

        void visit(StatementVisitor &visitor) override;
    };

    struct DiscardStatement : public Statement {
        auto get_type() -> StatementType override { return StatementType::DiscardStatement; }
        auto get_name() -> std::string_view override { return "DiscardStatement"; }

        void visit(StatementVisitor &visitor) override;
    };

    struct ReturnStatement : public Statement {
        auto get_type() -> StatementType override { return StatementType::ReturnStatement; }
        auto get_name() -> std::string_view override { return "ReturnStatement"; }

        void visit(StatementVisitor &visitor) override;

        ExpressionPtr expr;
    };

    struct DeclareVariableStatement : public Statement {
        auto get_type() -> StatementType override { return StatementType::DeclareVariableStatement; }
        auto get_name() -> std::string_view override { return "DeclareVariableStatement"; }

        void visit(StatementVisitor &visitor) override;

        std::string name;
        Token type;
        ExpressionPtr expression;
    };

    struct MultiStatement : public Statement {
        auto get_type() -> StatementType override { return StatementType::MultiStatement; }
        auto get_name() -> std::string_view override { return "MultiStatement"; }

        void visit(StatementVisitor &visitor) override;

        std::vector<StatementPtr> statements;
    };

    struct ScopedStatement : public Statement {
        auto get_type() -> StatementType override { return StatementType::ScopedStatement; }
        auto get_name() -> std::string_view override { return "ScopedStatement"; }

        void visit(StatementVisitor &visitor) override;

        StatementPtr statement;
    };

    struct ConditionalStatement {
        ExpressionPtr condition;
        StatementPtr statement;
    };

    struct BranchStatement : public Statement {
        auto get_type() -> StatementType override { return StatementType::BranchStatement; }
        auto get_name() -> std::string_view override { return "BranchStatement"; }

        void visit(StatementVisitor &visitor) override;

        std::vector<ConditionalStatement> conditional_statements;
        StatementPtr else_statement;
    };

    struct WhileStatement : public Statement {
        auto get_type() -> StatementType override { return StatementType::WhileStatement; }
        auto get_name() -> std::string_view override { return "WhileStatement"; }

        void visit(StatementVisitor &visitor) override;

        ExpressionPtr condition;
        StatementPtr statement;
    };

    struct ForStatement : public Statement {
        auto get_type() -> StatementType override { return StatementType::ForStatement; }
        auto get_name() -> std::string_view override { return "ForStatement"; }

        void visit(StatementVisitor &visitor) override;

        StatementPtr iterable;
        ExpressionPtr condition;
        ExpressionPtr step;
        StatementPtr statement;
    };

    struct ExpressionStatement : public Statement {
        auto get_type() -> StatementType override { return StatementType::ExpressionStatement; }
        auto get_name() -> std::string_view override { return "ExpressionStatement"; }

        void visit(StatementVisitor &visitor) override;

        ExpressionPtr expression;
    };

    struct LocationStatement : public Statement {
        auto get_type() -> StatementType override { return StatementType::LocationStatement; }
        auto get_name() -> std::string_view override { return "LocationStatement"; }

        void visit(StatementVisitor &visitor) override;

        u32 location;
        Token way;
        Token type;
        std::string name;
    };

    struct PrintStatement : public Statement {
        auto get_type() -> StatementType override { return StatementType::PrintStatement; }
        auto get_name() -> std::string_view override { return "PrintStatement"; }

        void visit(StatementVisitor &visitor) override;

        ExpressionPtr expression;
    };
} // namespace haflsl
