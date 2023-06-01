#include <haflsl/lexer.hpp>
#include <stdexcept>
#include <iostream>

namespace haflsl {
    Lexer::Lexer() {
        keywords["bool"] = TokenType::BOOL;
        keywords["int"] = TokenType::INT;
        keywords["float"] = TokenType::FLOAT;
        keywords["string"] = TokenType::STRING;
        keywords["fn"] = TokenType::FUNCTION;
        keywords["if"] = TokenType::IF;
        keywords["else"] = TokenType::ELSE;
        keywords["for"] = TokenType::FOR;
        keywords["while"] = TokenType::WHILE;
        keywords["return"] = TokenType::RETURN;
        keywords["and"] = TokenType::AND;
        keywords["or"] = TokenType::OR;
        keywords["struct"] = TokenType::STRUCT;

        keywords["print"] = TokenType::PRINT;
    }

    auto Lexer::peek(u32 offset) -> char {
        return content[index + offset];
    }

    auto Lexer::advance() -> char {
        index++;
        column++;
        return content[index - 1];
    }

    void Lexer::consume() {
        index++;
    }

    void Lexer::add_token(TokenType type) {
        tokens.push_back({.type = type,
                          .line = line,
                          .column = column,
                          .value = std::monostate{}});
    }

    void Lexer::skip_whitespace() {
        for (;;) {
            char c = peek(0);
            switch (c) {
                case ' ':
                case '\r':
                case '\t': advance(); break;
                case '\n':
                    line++;
                    column = 0;
                    advance();
                    break;
                case '/':
                    if (peek(1) == '/') {
                        while (peek(0) != '\n' && peek(0) != '\0') {
                            advance();
                        }
                    } else {
                        return;
                    }
                    break;
                default: return;
            }
        }
    }

    auto Lexer::is_alpha(char ch) -> bool {
        return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == '_';
    }

    auto Lexer::is_digit(char ch) -> bool {
        return ch >= '0' && ch <= '9';
    }

    auto Lexer::is_whitespace(char ch) -> bool {
        return ch != ' ' && ch != '\r' && ch != '\t' && ch != '\n' && ch != '\0';
    }

    void Lexer::identifier() {
        std::string identifier = {advance()};
        while (is_whitespace(peek(0) && (is_alpha(peek(0)) || is_digit(peek(0))))) {
            identifier += advance();
        }

        if (keywords.find(identifier) != keywords.end()) {
            add_token(keywords.at(identifier));
            return;
        }

        if (identifier == "true") {
            tokens.push_back({.type = TokenType::BOOL_CONSTANT,
                              .line = line,
                              .column = column,
                              .value = true});
        } else if (identifier == "false") {
            tokens.push_back({.type = TokenType::BOOL_CONSTANT,
                              .line = line,
                              .column = column,
                              .value = false});
        } else {
            tokens.push_back({.type = TokenType::IDENTIFIER,
                              .line = line,
                              .column = column,
                              .value = identifier});
        }
    }

    void Lexer::number() {
        std::string constant = {advance()};
        bool found_floating_point = false;

        while (is_digit(peek(0)) || peek(0) == '.') {
            char ch = advance();
            if (ch == '.') {
                found_floating_point = true;
            }
            constant += ch;
        }

        if (found_floating_point) {
            tokens.push_back({.type = TokenType::FLOAT_CONSTANT,
                              .line = line,
                              .column = 0,
                              .value = std::stod(constant)});
        } else {
            tokens.push_back({.type = TokenType::INT_CONSTANT,
                              .line = line,
                              .column = 0,
                              .value = std::stol(constant)});
        }
    }

    void Lexer::string_constant() {
    }

    auto Lexer::tokenize(const Global &global, const std::string &data) -> Result<std::vector<Token>> {

        content = data;
        tokens.clear();
        index = 0;
        line = 1;
        column = 1;

        while (peek(0) != '\0' || index + 1 == content.size() || peek(0) == 0) {
            skip_whitespace();

            if (is_alpha(peek(0))) {
                identifier();
                continue;
            }
            if (is_digit(peek(0))) {
                number();
                continue;
            }

            switch (peek(0)) {
                case '(': {
                    add_token(TokenType::LEFT_PAREN);
                    break;
                }
                case ')': {
                    add_token(TokenType::RIGHT_PAREN);
                    break;
                }
                case '{': {
                    add_token(TokenType::LEFT_BRACE);
                    break;
                }
                case '}': {
                    add_token(TokenType::RIGHT_BRACE);
                    break;
                }
                case '[': {
                    add_token(TokenType::LEFT_BRACKET);
                    break;
                }
                case ']': {
                    add_token(TokenType::RIGHT_BRACKET);
                    break;
                }

                case '.': {
                    add_token(TokenType::DOT);
                    break;
                }
                case ',': {
                    add_token(TokenType::COMMA);
                    break;
                }
                case ';': {
                    add_token(TokenType::SEMICOLON);
                    break;
                }

                case '+': {
                    if (peek(1) == '=') {
                        add_token(TokenType::PLUS_ASSIGN);
                        consume();
                    } else if (peek(1) == '+') {
                        add_token(TokenType::INCREMENT);
                        consume();
                    } else {
                        add_token(TokenType::PLUS);
                    }
                    break;
                }

                case '-': {
                    if (peek(1) == '=') {
                        add_token(TokenType::MINUS_ASSIGN);
                        consume();
                    } else if (peek(1) == '-') {
                        add_token(TokenType::DECREMENT);
                        consume();
                    } else if (peek(1) == '>') {
                        add_token(TokenType::ARROW);
                        consume();
                    } else {
                        add_token(TokenType::MINUS);
                    }
                    break;
                }

                case '*': {
                    if (peek(1) == '=') {
                        add_token(TokenType::STAR_ASSIGN);
                        consume();
                    } else {
                        add_token(TokenType::STAR);
                    }
                    break;
                }

                case '/': {
                    if (peek(1) == '=') {
                        add_token(TokenType::SLASH_ASSIGN);
                        consume();
                    } else {
                        add_token(TokenType::SLASH);
                    }
                    break;
                }

                case '%': {
                    if (peek(1) == '=') {
                        add_token(TokenType::MODULO_ASSIGN);
                        consume();
                    } else {
                        add_token(TokenType::MODULO);
                    }
                    break;
                }

                case '!': {
                    if (peek(1) == '=') {
                        add_token(TokenType::BANG_EQUAL);
                        consume();
                    } else {
                        add_token(TokenType::BANG);
                    }
                    break;
                }

                case '=': {
                    if (peek(1) == '=') {
                        add_token(TokenType::EQUAL_EQUAL);
                        consume();
                    } else {
                        add_token(TokenType::EQUAL);
                    }
                    break;
                }

                case '>': {
                    if (peek(1) == '=') {
                        add_token(TokenType::GREATER_EQUAL);
                        consume();
                    } else {
                        add_token(TokenType::GREATER);
                    }
                    break;
                }

                case '<': {
                    if (peek(1) == '=') {
                        add_token(TokenType::LESS_EQUAL);
                        consume();
                    } else {
                        add_token(TokenType::LESS);
                    }
                    break;
                }

                case '"': {

                    consume();
                    std::string constant = {};
                    while (peek(0) != '"') {
                        constant += advance();
                    }

                    tokens.push_back({.type = TokenType::STRING_CONSTANT,
                                      .line = line,
                                      .column = 0,
                                      .value = constant});

                    break;
                }

                default: {
                    if (index + 1 >= content.size()) {
                        add_token(TokenType::EOS);
                        return Result<std::vector<Token>>(tokens);
                    }

                    // return Result<std::vector<Token>>("token " + std::string{peek(0)} + " on line: " + std::to_string(line) + " and column: " + std::to_string(column) + " couldn't be parsed");
                    return Result<std::vector<Token>>(global.make_error_message(line, column, "unknown token"));
                }
            }

            advance();
        }

        add_token(TokenType::EOS);

        return Result<std::vector<Token>>(tokens);
    }
} // namespace haflsl