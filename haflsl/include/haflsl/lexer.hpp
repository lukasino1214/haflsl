#pragma once
#include "token.hpp"

#include <vector>
#include <string>
#include <unordered_map>

namespace HAFLSL {
    struct Lexer {
        Lexer();

        auto tokenize(const std::string& src) -> std::vector<Token>;
        void print_token(const std::string& src, const Token& token);

        std::unordered_map<std::string_view, TokenType> keywords{};
    };
}