#pragma once
#include "types.hpp"
#include <memory>
#include <vector>
#include "logger.hpp"
#include "token.hpp"
#include "uuid.hpp"

namespace HAFLSL {
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

    using ExpressionPtr = std::unique_ptr<Expression>;

    struct Expression {
        Expression() = default;
        Expression(const Expression&) = delete;
        Expression(Expression&&) noexcept = default;
        virtual ~Expression() = default;

        virtual auto get_type() -> ExpressionType = 0;
        virtual auto get_name() -> std::string_view = 0;

        Expression& operator=(const Expression&) = delete;
        Expression& operator=(Expression&&) noexcept = default;

        UUID uuid = UUID();
    };

    struct ConstantValueExpression : public Expression {
        auto get_type() -> ExpressionType override { return ExpressionType::ConstantValueExpression; }
        auto get_name() -> std::string_view override { return "ConstantValueExpression"; }

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

        UnaryType type;
        ExpressionPtr expr;
    };

    struct IdentifierExpression : public Expression {
        auto get_type() -> ExpressionType override { return ExpressionType::IdentifierExpression; }
        auto get_name() -> std::string_view override { return "IdentifierExpression"; }

        std::string_view name;
    };

    struct AccessIdentifierExpression : public Expression {
        auto get_type() -> ExpressionType override { return ExpressionType::AccessIdentifierExpression; }
        auto get_name() -> std::string_view override { return "AccessIdentifierExpression"; }

		std::vector<std::string_view> identifiers;
		ExpressionPtr expr;
    };

    struct AccessIndexExpression : public Expression {
        auto get_type() -> ExpressionType override { return ExpressionType::AccessIndexExpression; }
        auto get_name() -> std::string_view override { return "AccessIndexExpression"; }

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

        AssignType type;
        ExpressionPtr left;
        ExpressionPtr right;
    };

    struct CallFunctionExpression : public Expression {
        auto get_type() -> ExpressionType override { return ExpressionType::CallFunctionExpression; }
        auto get_name() -> std::string_view override { return "CallFunctionExpression"; }

        ExpressionPtr function_expr;
        std::vector<ExpressionPtr> parameters;
    };

    struct ConstructorExpression : public Expression {
        auto get_type() -> ExpressionType override { return ExpressionType::ConstructorExpression; }
        auto get_name() -> std::string_view override { return "ConstructorExpression"; }

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
    };

    struct Statement;

    using StatementPtr = std::unique_ptr<Statement>;

    struct Statement {
        Statement() = default;
        Statement(const Statement&) = delete;
        Statement(Statement&&) noexcept = default;
        virtual ~Statement() = default;

        virtual auto get_type() -> StatementType = 0;
        virtual auto get_name() -> std::string_view = 0;

        Statement& operator=(const Statement&) = delete;
        Statement& operator=(Statement&&) noexcept = default;

        UUID uuid = UUID();
    };

    struct StructMember {
        Token token;
        std::string_view name;
    };

    struct DeclareStructStatement : public Statement {
        auto get_type() -> StatementType override { return StatementType::DeclareStructStatement; }
        auto get_name() -> std::string_view override { return "DeclareStructStatement"; }

        std::string_view name;
        std::vector<StructMember> members;
    };

    struct Parameter {
        Token token;
        std::string_view name;
    };

    struct DeclareFunctionStatement : public Statement {
        auto get_type() -> StatementType override { return StatementType::DeclareFunctionStatement; }
        auto get_name() -> std::string_view override { return "DeclareFunctionStatement"; }

        std::string_view name;
        Token returned_type;
        std::vector<Parameter> parameters;
        std::vector<StatementPtr> statements;
    };

    struct BreakStatement : public Statement {
        auto get_type() -> StatementType override { return StatementType::BreakStatement; }
        auto get_name() -> std::string_view override { return "BreakStatement"; }
    };

    struct ContinueStatement : public Statement {
        auto get_type() -> StatementType override { return StatementType::ContinueStatement; }
        auto get_name() -> std::string_view override { return "ContinueStatement"; }
    };

    struct DiscardStatement : public Statement {
        auto get_type() -> StatementType override { return StatementType::DiscardStatement; }
        auto get_name() -> std::string_view override { return "DiscardStatement"; }
    };

    struct ReturnStatement : public Statement {
        auto get_type() -> StatementType override { return StatementType::ReturnStatement; }
        auto get_name() -> std::string_view override { return "ReturnStatement"; }
    
        ExpressionPtr expr;
    };

    struct DeclareVariableStatement : public Statement {
        auto get_type() -> StatementType override { return StatementType::DeclareVariableStatement; }
        auto get_name() -> std::string_view override { return "DeclareVariableStatement"; }

        std::string_view name;
        Token type;
        ExpressionPtr expression;
    };

    struct MultiStatement : public Statement {
        auto get_type() -> StatementType override { return StatementType::MultiStatement; }
        auto get_name() -> std::string_view override { return "MultiStatement"; }

        std::vector<StatementPtr> statements;
    };

    struct ScopedStatement : public Statement {
        auto get_type() -> StatementType override { return StatementType::ScopedStatement; }
        auto get_name() -> std::string_view override { return "ScopedStatement"; }

        StatementPtr statement;
    };

    struct ConditionalStatement {
        ExpressionPtr condition;
        StatementPtr  statement;
    };

    struct BranchStatement : public Statement {
        auto get_type() -> StatementType override { return StatementType::BranchStatement; }
        auto get_name() -> std::string_view override { return "BranchStatement"; }

        std::vector<ConditionalStatement> conditional_statements;
		StatementPtr else_statement;
    };

    struct WhileStatement : public Statement {
        auto get_type() -> StatementType override { return StatementType::WhileStatement; }
        auto get_name() -> std::string_view override { return "WhileStatement"; }

        ExpressionPtr condition;
		StatementPtr statement;
    };

    struct ForStatement : public Statement {
        auto get_type() -> StatementType override { return StatementType::ForStatement; }
        auto get_name() -> std::string_view override { return "ForStatement"; }

        StatementPtr iterable;
        ExpressionPtr condition;
        ExpressionPtr step;
		StatementPtr statement;
    };

    struct ExpressionStatement : public Statement {
        auto get_type() -> StatementType override { return StatementType::ExpressionStatement; }
        auto get_name() -> std::string_view override { return "ExpressionStatement"; }

        ExpressionPtr expression;
    };

    struct LocationStatement : public Statement {
        auto get_type() -> StatementType override { return StatementType::LocationStatement; }
        auto get_name() -> std::string_view override { return "LocationStatement"; }

        u32 location;
        Token way;
        Token type;
        std::string_view name;
    };
}