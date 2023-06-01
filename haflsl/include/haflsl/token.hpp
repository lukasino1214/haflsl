#pragma once

#include <variant>
#include <string>

#include <haflsl/types.hpp>

namespace haflsl {
    enum struct TokenType : u32 {
        LEFT_PAREN,    // (
        RIGHT_PAREN,   // )
        LEFT_BRACE,    // {
        RIGHT_BRACE,   // }
        LEFT_BRACKET,  // [
        RIGHT_BRACKET, // ]

        DOT,       // .
        COMMA,     // ,
        SEMICOLON, // ;
        ARROW,     // ->

        PLUS,          // +
        PLUS_ASSIGN,   // +=
        INCREMENT,     // ++
        MINUS,         // -
        MINUS_ASSIGN,  // -=
        DECREMENT,     // --
        STAR,          // *
        STAR_ASSIGN,   // *=
        SLASH,         // /
        SLASH_ASSIGN,  // /=
        MODULO,        // %
        MODULO_ASSIGN, // %=

        BANG,          // !
        BANG_EQUAL,    // !=
        EQUAL,         // =
        EQUAL_EQUAL,   // ==
        GREATER,       // >
        GREATER_EQUAL, // >=
        LESS,          // <
        LESS_EQUAL,    // <=

        VOID,   // void
        BOOL,   // bool
        INT,    // int
        FLOAT,  // float
        STRING, // string

        IDENTIFIER, // name of variable, function, member

        BOOL_CONSTANT,   // true / false
        INT_CONSTANT,    // 1451515
        FLOAT_CONSTANT,  // 14489.5
        STRING_CONSTANT, // "dawwad"

        FUNCTION, // fn
        IF,       // if
        ELSE,     // else
        FOR,      // for
        WHILE,    // while
        RETURN,   // return

        AND,    // and
        OR,     // or
        STRUCT, // struct

        PRINT, // print
        EOS,   // indicates end of the stream
    };

    struct Token {
        TokenType type;
        u32 line, column;
        std::variant<std::monostate, bool, i64, f64, std::string> value = std::monostate{};

        void print() const;
        auto type_to_str() const -> std::string;
    };
} // namespace haflsl