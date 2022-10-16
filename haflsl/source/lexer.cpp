#include <haflsl/lexer.hpp>
#include <haflsl/logger.hpp>

namespace HAFLSL {
    auto Lexer::tokenize(const std::string& src) -> std::vector<Token> {
        std::vector<Token> tokens;
        bool string = false;
        u32 pos = 0;
        for(u32 i = 0; i < src.size(); i++) {
            if(src[i] != ' ' && src[i] != '\n') {
                switch(src[i]) {
                    case '(':
                        tokens.push_back({TokenType::LPAREN, i, 1});
                        break;
                    case ')':
                        tokens.push_back({TokenType::RPAREN, i, 1});
                        break;
                    case '{':
                        tokens.push_back({TokenType::LBRACKET, i, 1});
                        break;
                    case '}':
                        tokens.push_back({TokenType::RBRACKET, i, 1});
                        break;
                    case ',':
                        tokens.push_back({TokenType::COMMA, i, 1});
                        break;
                    case ';':
                        tokens.push_back({TokenType::SEMICOLON, i, 1});
                        break;
                    case '=': // can be a problem
                        tokens.push_back({TokenType::ASSIGN, i, 1});
                        break;
                    default:
                        u32 pos = i;
                        while(true) {
                            if(src[pos] == ' ' || src[pos] == '(' || src[pos] == '=' || src[pos] == ')' || src[pos] == ',') {
                                tokens.push_back({TokenType::ID, i, pos - i});
                                i = pos;
                                break;
                            }
                            pos++;
                        }
                        break;
                }
            }
        }
        return tokens;
    }

    auto Lexer::token_to_string_view(const std::string& src, const Token& token) -> std::string_view {
        switch(token.type) {
            case TokenType::LPAREN:
                return "(";
            case TokenType::RPAREN:
                return ")";
            case TokenType::LBRACKET:
                return "{";
            case TokenType::RBRACKET:
                return "}";
            case TokenType::COMMA:
                return ",";
            case TokenType::SEMICOLON:
                return ";";
            case TokenType::ASSIGN:
                return "=";
            case TokenType::ID:
                return std::string_view{src.data() + token.index, token.len};
            default:
                return "wtf";
        }
    }

    void Lexer::print_token(const std::string& src, const Token& token) {
        switch(token.type) {
            case TokenType::LPAREN:
                INFO("TOKEN TYPE: LPAREN \t VALUE: (");
                break;
            case TokenType::RPAREN:
                INFO("TOKEN TYPE: RPAREN \t VALUE: )");
                break;
            case TokenType::LBRACKET:
                INFO("TOKEN TYPE: LBRACKET  VALUE: {");
                break;
            case TokenType::RBRACKET:
                INFO("TOKEN TYPE: RBRACKET  VALUE: }");
                break;
            case TokenType::COMMA:
                INFO("TOKEN TYPE: COMMA \t VALUE: ,");
                break;
            case TokenType::SEMICOLON:
                INFO("TOKEN TYPE: SEMICOLON VALUE: ;");
                break;
            case TokenType::ASSIGN:
                INFO("TOKEN TYPE: ASSIGN \t VALUE: =");
                break;
            case TokenType::ID:
                INFO("TOKEN TYPE: ID \t VALUE: {}", src.substr(token.index, token.len));
                break;
            default:
                INFO("TOKEN TYPE: UNKNOWN \t VALUE: UNKNOWN");
                break;
        }
    }
}