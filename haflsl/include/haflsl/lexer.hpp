#pragma once
#include "token.hpp"

#include <vector>
#include <string>

namespace HAFLSL {
    namespace Lexer {
        auto tokenize(const std::string& src) -> std::vector<Token>;
        auto token_to_string_view(const std::string& src, const Token& token) -> std::string_view;
        void print_token(const std::string& src, const Token& token);
    }
}