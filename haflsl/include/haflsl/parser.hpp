#pragma once

#include "token.hpp"
#include "statement.hpp"
#include <vector>
#include <string>

namespace HAFLSL {
    struct Parser {
        Parser() = default;
        ~Parser() = default;

        void parse(const std::vector<Token>& tokens);


        struct Context {
            usize token_count = 0;
            usize token_index = 0;
            const Token* tokens;
        };

        auto peek(usize advance = 0) -> const Token&;
        auto advance() -> const Token&;
        void consume(usize count = 1);

        auto is_type(TokenType type) -> bool;

        auto expect(const Token& token, TokenType type) -> const Token&;
        auto expect_not(const Token& token, TokenType type) -> const Token&;
        auto expect(TokenType type) -> const Token&;

        auto parse_root_statement() -> StatementPtr;
        auto parse_function_declaration() -> StatementPtr;
        auto parse_variable_declaration() -> StatementPtr;
        auto parse_struct_declaration() -> StatementPtr;

        Context* context;
    };
}