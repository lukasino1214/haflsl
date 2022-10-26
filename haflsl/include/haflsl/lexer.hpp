#pragma once
#include "token.hpp"

#include <vector>
#include <string>
#include <unordered_map>

namespace HAFLSL {
    struct Lexer {
        Lexer();

        auto tokenize(const std::string& src) -> std::vector<Token>;
        static void print_token(const std::string& src, const Token& token);
        static auto token_to_string_view(const Token& token) -> std::string_view;

        std::unordered_map<std::string_view, TokenType> keywords{};
    };
}