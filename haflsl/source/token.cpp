
#include <haflsl/token.hpp>

#include <iostream>

static constexpr std::string_view token_names[] = {
    "LEFT_PAREN",
    "RIGHT_PAREN",
    "LEFT_BRACE",
    "RIGHT_BRACE",
    "LEFT_BRACKET",
    "RIGHT_BRACKET",

    "DOT",
    "COMMA",
    "SEMICOLON",
    "ARROW",

    "PLUS",
    "PLUS_ASSIGN",
    "INCREMENT",
    "MINUS",
    "MINUS_ASSIGN",
    "DECREMENT",
    "STAR",
    "STAR_ASSIGN",
    "SLASH",
    "SLASH_ASSIGN",
    "MODULO",
    "MODULO_ASSIGN",

    "BANG",
    "BANG_EQUAL",
    "EQUAL",
    "EQUAL_EQUAL",
    "GREATER",
    "GREATER_EQUAL",
    "LESS",
    "LESS_EQUAL",

    "VOID",
    "BOOL",
    "INT",
    "FLOAT",
    "STRING",

    "VEC2",
    "VEC3",
    "VEC4",

    "IVEC2",
    "IVEC3",
    "IVEC4",

    "IDENTIFIER",

    "BOOL_CONSTANT",
    "INT_CONSTANT",
    "FLOAT_CONSTANT",
    "STRING_CONSTANT",

    "FUNCTION",
    "IF",
    "ELSE",
    "FOR",
    "WHILE",
    "RETURN",

    "AND",
    "OR",

    "STRUCT",

    "LAYOUT",
    "LOCATION",

    "IN",
    "OUT",

    "PRINT",
    "EOS"};

namespace haflsl {
    void Token::print() const {
        std::string token_value;
        if (static_cast<u32>(type) >= static_cast<u32>(TokenType::IDENTIFIER) && static_cast<u32>(type) <= static_cast<u32>(TokenType::STRING_CONSTANT)) {
            token_value += " VALUE: ";
            if (type == TokenType::IDENTIFIER) {
                token_value += std::get<std::string>(value);
            } else if (type == TokenType::BOOL_CONSTANT) {
                token_value += std::get<bool>(value) ? "true" : "false";
            } else if (type == TokenType::INT_CONSTANT) {
                token_value += std::to_string(std::get<i64>(value));
            } else if (type == TokenType::FLOAT_CONSTANT) {
                token_value += std::to_string(std::get<f64>(value));
            } else if (type == TokenType::STRING_CONSTANT) {
                token_value += std::get<std::string>(value);
            }
        }

        std::cout << token_names[static_cast<u32>(type)] << token_value << std::endl;
    }

    auto Token::type_to_str() const -> std::string {
        return std::string{token_names[static_cast<u32>(type)]};
    }
} // namespace haflsl