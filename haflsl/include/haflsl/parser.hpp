#pragma once

#include <vector>

#include <haflsl/token.hpp>
#include <haflsl/nodes.hpp>
#include <haflsl/result.hpp>
#include <haflsl/global.hpp>

namespace haflsl {
    struct AST {
        std::vector<StatementPtr> statements = {};
    };

    struct Parser {
        Parser() = default;
        ~Parser() = default;

        struct Context {
            usize token_count = 0;
            usize token_index = 0;
            const Token *tokens;
        };

        auto peek(usize advance = 0) -> const Token &;
        auto advance() -> const Token &;
        void consume(usize count = 1);

        auto expect(const Token &token, TokenType type) -> const Token &;
        auto expect_not(const Token &token, TokenType type) -> const Token &;
        auto expect(TokenType type) -> const Token &;

        auto is_type(TokenType type) -> bool;
        auto is_constant(TokenType type) -> bool;

        void debug_print(const AST &ast);
        auto parse(const Global& global, std::vector<Token> tokens) -> Result<std::vector<StatementPtr>>;

        auto parse_root_statement() -> StatementPtr;
        auto parse_print_statement() -> StatementPtr;
        auto parse_function_declaration() -> StatementPtr;
        auto parse_variable_declaration() -> StatementPtr;
        auto parse_statement_list() -> std::vector<StatementPtr>;
        auto parse_single_statement() -> StatementPtr;
        auto parse_statement() -> StatementPtr;
        auto parse_return_statement() -> StatementPtr;
        auto parse_expression_statement() -> ExpressionPtr;
        auto parse_branch_statement() -> StatementPtr;
        auto parse_while_statement() -> StatementPtr;
        auto parse_for_statement() -> StatementPtr;
        auto parse_struct_declaration() -> StatementPtr;

        auto parse_expression() -> ExpressionPtr;
        auto parse_bin_op_rhs(i32 expr_precedence, ExpressionPtr lhs) -> ExpressionPtr;
        auto parse_primary_expression() -> ExpressionPtr;
        auto parse_constant_expression() -> ExpressionPtr;
        auto parse_parenthesis_expression() -> ExpressionPtr;
        auto parse_expression_list() -> std::vector<ExpressionPtr>;

        auto get_token_precedence(const TokenType &token) -> i32;

        auto build_identifier_access(ExpressionPtr lhs, ExpressionPtr rhs) -> ExpressionPtr;
        auto build_binary(BinaryType binary_type, ExpressionPtr lhs, ExpressionPtr rhs) -> ExpressionPtr;

        Context *context;
    };
} // namespace haflsl