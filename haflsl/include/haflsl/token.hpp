#pragma once
#include "types.hpp"

namespace HAFLSL {
    enum struct TokenType : u32 {
        ID,                // string
        ASSIGN,            // =
        LPAREN,            // (
        RPAREN,            // )
        LBRACKET,          // {
        RBRACKET,          // }
        COMMA,             // , 
        SEMICOLON,         // ;
        LARRAY,            // [
        RARRAY,            // ]
        DOT,               // .

        // OPERATORS
        INCREMENT,         // ++,
        DECREMENT,         // --
        PLUS,              // +,
        MINUS,             // -
        NEGATE,            // !
        MULTIPLY,          // *
        DIVIDE,            // /
        LESS,              // <
        GREATER,           // >
        LESS_AND_EQUAL,    // <=
        GREATER_AND_EQUAL, // >=
        EQUAL,             // ==
        NOT_EQUAL,         // !=
        AND,               // &&
        OR_EX,      // ^^
        OR_IN,      // ||
        // add ? :
        ASSIGN_ADD,        // +=
        ASSIGN_SUB,        // -=
        ASSIGN_MUL,        // *=
        ASSIGN_DIV,        // /=
        /*
        MODULO, // %
        BITWISE_LEFT, // <<
        BITWISE_RIGHT // >>
        BITWISE_AND // &
        BITWISE_OR_EXCLUSIVE // ^
        BITWISE_OR_INCLUSIVE // |
        */
        END,

        VOID,
        VEC3,
        VEC4
    };

    struct Token {
        TokenType type;
        usize index, len;
    };
}