#pragma once
#include "types.hpp"

namespace HAFLSL {
    enum struct TokenType : u32 {
        ID,
        ASSIGN,
        LPAREN,
        RPAREN,
        LBRACKET,
        RBRACKET,
        COMMA,
        SEMICOLON,
        END
    };

    struct Token {
        TokenType type;
        usize index, len;
    };
}