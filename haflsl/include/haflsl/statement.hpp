#pragma once
#include "types.hpp"
#include <memory>
#include <vector>
#include "logger.hpp"

namespace HAFLSL {
    enum class StatementType : u32 {
        BreakStatement,
        ContinueStatement,
        DiscardStatement,
        DeclareFunctionStatement,
        DeclareStructStatement,
        //BranchStatement,
        //ConditionalStatement,
        //DeclareConstStatement,
        /*DeclareVariableStatement,
        DiscardStatement,
        ForStatement,
        ExpressionStatement,
        MultiStatement,
        NoOpStatement,
        ReturnStatement,
        ScopedStatement,
        WhileStatement,*/
    };

    struct Statement;

    using StatementPtr = std::unique_ptr<Statement>;

    struct Statement {
        Statement() = default;
        Statement(const Statement&) = delete;
        Statement(Statement&&) noexcept = default;
        virtual ~Statement() = default;

        virtual auto get_type() -> StatementType const = 0;

        Statement& operator=(const Statement&) = delete;
        Statement& operator=(Statement&&) noexcept = default;
    };

    struct StructMember {
        Token token;
        std::string_view name;
    };

    struct DeclareStructStatement : public Statement {
        auto get_type() -> StatementType const override { return StatementType::DeclareStructStatement; }

        std::string_view name;
        std::vector<StructMember> members;
    };

    struct Parameter {
        Token token;
        std::string_view name;
    };

    struct DeclareFunctionStatement : public Statement {
        auto get_type() -> StatementType const override { return StatementType::DeclareFunctionStatement; }

        std::string_view name;
        Token returned_type;
        std::vector<Parameter> parameters;
        // std::vector<> stmts;
    };

    struct BreakStatement : public Statement {
        auto get_type() -> StatementType const override { return StatementType::BreakStatement; }
    };

    struct ContinueStatement : public Statement {
        auto get_type() -> StatementType const override { return StatementType::ContinueStatement; }
    };

    struct DiscardStatement : public Statement {
        auto get_type() -> StatementType const override { return StatementType::DiscardStatement; }
    };
}