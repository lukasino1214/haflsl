#pragma once

#include <haflsl/token.hpp>
#include <haflsl/result.hpp>
#include <haflsl/global.hpp>

#include <vector>
#include <string>
#include <unordered_map>

namespace haflsl {
    struct Lexer {
        Lexer();
        ~Lexer() = default;

        auto tokenize(const Global& global, const std::string &data) -> Result<std::vector<Token>>;

    private:
        auto peek(u32 offset) -> char;
        auto advance() -> char;
        void consume();

        void skip_whitespace();
        void identifier();
        void number();
        void string_constant();

        auto is_alpha(char ch) -> bool;
        auto is_digit(char ch) -> bool;
        auto is_whitespace(char ch) -> bool;

        void add_token(TokenType type);

        template <typename T>
        void add_token(TokenType type, T value);

        std::unordered_map<std::string, TokenType> keywords = {};

        std::string content = {};
        std::vector<Token> tokens = {};
        u32 index = 0;
        u32 line = 0;
        u32 column = 0;
    };
} // namespace haflsl