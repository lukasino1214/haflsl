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
                    case '[':
                        tokens.push_back({TokenType::LARRAY, i, 1});
                        break;
                    case ']':
                        tokens.push_back({TokenType::RARRAY, i, 1});
                        break;
                    case '&':
                        if(src[i+1] == '&') {
                            tokens.push_back({TokenType::AND, i, 2});
                            i += 1;
                        }
                        break;
                    case '^':
                        if(src[i+1] == '^') {
                            tokens.push_back({TokenType::OR_EX, i, 2});
                            i += 1;
                            break;
                        }
                        break;
                    case '|':
                        if(src[i+1] == '|') {
                            tokens.push_back({TokenType::OR_IN, i, 2});
                            i += 1;
                            break;
                        }
                        break;
                    case '!':
                        if(src[i+1] == '=') {
                            tokens.push_back({TokenType::NOT_EQUAL, i, 2});
                            i += 1; // i += 1 so it skips =
                        } else {
                            tokens.push_back({TokenType::NEGATE, i, 1});
                        }
                        break;
                    case '*':
                        if(src[i+1] == '=') {
                            tokens.push_back({TokenType::ASSIGN_MUL, i, 2});
                            i += 1;
                        } else {
                            tokens.push_back({TokenType::MULTIPLY, i, 1});
                        }
                        break;
                    case '/':
                        if(src[i+1] == '=') {
                            tokens.push_back({TokenType::ASSIGN_DIV, i, 2});
                            i += 1;
                        } else {
                            tokens.push_back({TokenType::DIVIDE, i, 1});
                        }
                        break;
                   case '>':
                        if(src[i+1] == '=') {
                            tokens.push_back({TokenType::LESS_AND_EQUAL, i, 2});
                            i += 1;
                        } else {
                            tokens.push_back({TokenType::LESS, i, 1});
                        }
                        break;
                    case '<':
                        if(src[i+1] == '=') {
                            tokens.push_back({TokenType::GREATER_AND_EQUAL, i, 2});
                            i += 1;
                        } else {
                            tokens.push_back({TokenType::GREATER, i, 1});
                        }
                        break;
                    case '=':
                        if(src[i+1] == '=') {
                            tokens.push_back({TokenType::EQUAL, i, 2});
                            i += 1;
                        } else {
                            tokens.push_back({TokenType::ASSIGN, i, 1});
                        }
                        break;
                    case '+':
                        if(src[i+1] == '=') {
                            tokens.push_back({TokenType::ASSIGN_ADD, i, 2});
                            i += 1;
                        } else if(src[i+1] == '+') {
                            tokens.push_back({TokenType::INCREMENT, i, 2});
                            i += 1;
                        } else {
                            tokens.push_back({TokenType::PLUS, i, 1});
                        }
                        break;
                    case '-':
                        if(src[i+1] == '=') {
                            tokens.push_back({TokenType::ASSIGN_SUB, i, 2});
                            i += 1;
                        } else if(src[i+1] == '-') {
                            tokens.push_back({TokenType::DECREMENT, i, 2});
                            i += 1;
                        } else {
                            tokens.push_back({TokenType::MINUS, i, 1});
                        }
                        break;
                    default:
                        u32 pos = i;
                        while(true) {
                            if(src[pos] == ' ' || src[pos] == '(' || src[pos] == '=' || src[pos] == ')' || src[pos] == ',' || src[pos] == '\n') {
                                tokens.push_back({TokenType::ID, i, pos - i});
                                i = pos - 1;
                                break;
                            }
                            pos++;
                        }
                        break;
                }
            }
        }

        /*for(auto& token : tokens) {
            if(token.type == TokenType::ID) {

            }
        }*/
        for(u32 i = 0; i < tokens.size(); i++) {
            if(tokens[i].type == TokenType::ID) {
                if(tokens[i+1].type != TokenType::LPAREN) {
                    std::string_view view = std::string_view(src.data() + tokens[i].index, tokens[i].len);
                    if(view == "vec3") {
                        tokens[i].type = TokenType::VEC3;
                    } else if(view == "vec4") {
                        tokens[i].type = TokenType::VEC4;
                    } else if(view == "void") {
                        tokens[i].type = TokenType::VOID;
                    }
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
            case TokenType::LARRAY:
                return "[";
            case TokenType::RARRAY:
                return "]";
            case TokenType::DIVIDE:
                return "/";
            case TokenType::ASSIGN_DIV:
                return "=";
            case TokenType::AND:
                return "&&";
            case TokenType::OR_EX:
                return "^^";
            case TokenType::OR_IN:
                return "||";
            case TokenType::EQUAL:
                return "==";
            case TokenType::NEGATE:
                return "!";
            case TokenType::NOT_EQUAL:
                return "!=";
            case TokenType::MULTIPLY:
                return "*";
            case TokenType::ASSIGN_MUL:
                return "*=";
            case TokenType::PLUS:
                return "+";
            case TokenType::INCREMENT:
                return "++";
            case TokenType::ASSIGN_ADD:
                return "+=";
            case TokenType::MINUS:
                return "-";
            case TokenType::DECREMENT:
                return "--";
            case TokenType::ASSIGN_SUB:
                return "-=";
            case TokenType::VEC3:
                return "vec3";
            case TokenType::VEC4:
                return "vec4";
            case TokenType::VOID:
                return "void";
            case TokenType::ID:
                return std::string_view{src.data() + token.index, token.len};
            default:
                return "wtf";
        }
    }

    void Lexer::print_token(const std::string& src, const Token& token) {
        switch(token.type) {
            case TokenType::LPAREN:
                INFO("TOKEN TYPE: LPAREN \t\t VALUE: (");
                break;
            case TokenType::RPAREN:
                INFO("TOKEN TYPE: RPAREN \t\t VALUE: )");
                break;
            case TokenType::LBRACKET:
                INFO("TOKEN TYPE: LBRACKET \t VALUE: {");
                break;
            case TokenType::RBRACKET:
                INFO("TOKEN TYPE: RBRACKET \t VALUE: }");
                break;
            case TokenType::COMMA:
                INFO("TOKEN TYPE: COMMA \t\t VALUE: ,");
                break;
            case TokenType::SEMICOLON:
                INFO("TOKEN TYPE: SEMICOLON \t VALUE: ;");
                break;
            case TokenType::ASSIGN:
                INFO("TOKEN TYPE: ASSIGN \t\t VALUE: =");
                break;
            case TokenType::ID:
                INFO("TOKEN TYPE: ID \t\t VALUE: {}", src.substr(token.index, token.len));
                break;
            case TokenType::LARRAY:
                INFO("TOKEN TYPE: LARRAY \t\t VALUE: [");
                break;
            case TokenType::RARRAY:
                INFO("TOKEN TYPE: RARRAY \t\t VALUE: ]");
                break;
            case TokenType::DIVIDE:
                INFO("TOKEN TYPE: DIVIDE \t\t VALUE: /");
                break;
            case TokenType::ASSIGN_DIV:
                INFO("TOKEN TYPE: ASSIGN_DIV \t VALUE: /=");
                break;
            case TokenType::MULTIPLY:
                INFO("TOKEN TYPE: MULTIPLY \t VALUE: *");
                break;
            case TokenType::ASSIGN_MUL:
                INFO("TOKEN TYPE: ASSIGN_MUL \t VALUE: *=");
                break;
            case TokenType::AND:
                INFO("TOKEN TYPE: AND \t\t VALUE: &&");
                break;
            case TokenType::NEGATE:
                INFO("TOKEN TYPE: NEGATE \t\t VALUE: !");
                break;
            case TokenType::EQUAL:
                INFO("TOKEN TYPE: EQUAL \t\t VALUE: ==");
                break;
            case TokenType::NOT_EQUAL:
                INFO("TOKEN TYPE: NOT_EQUAL \t VALUE: !=");
                break;
            case TokenType::OR_EX:
                INFO("TOKEN TYPE: OR_EX \t\t VALUE: ^^");
                break;
            case TokenType::OR_IN:
                INFO("TOKEN TYPE: OR_IN \t\t VALUE: ||");
                break;
            case TokenType::LESS:
                INFO("TOKEN TYPE: LESS \t\t VALUE: <");
                break;
            case TokenType::GREATER:
                INFO("TOKEN TYPE: GREATER \t\t VALUE: >");
                break;
            case TokenType::LESS_AND_EQUAL:
                INFO("TOKEN TYPE: LESS_AND_EQUAL    VALUE: <=");
                break;
            case TokenType::GREATER_AND_EQUAL:
                INFO("TOKEN TYPE: GREATER_AND_EQUAL VALUE: >=");
                break;
            case TokenType::PLUS:
                INFO("TOKEN TYPE: PLUS \t\t VALUE: +");
                break;
            case TokenType::INCREMENT:
                INFO("TOKEN TYPE: INCREMENT \t VALUE: ++");
                break;
            case TokenType::ASSIGN_ADD:
                INFO("TOKEN TYPE: ASSIGN_ADD \t VALUE: +=");
                break;
            case TokenType::MINUS:
                INFO("TOKEN TYPE: MINUS \t\t VALUE: -");
                break;
            case TokenType::DECREMENT:
                INFO("TOKEN TYPE: DECREMENT \t VALUE: --");
                break;
            case TokenType::ASSIGN_SUB:
                INFO("TOKEN TYPE: ASSIGN_SUB \t VALUE: -=");
                break;
            case TokenType::VEC3:
                INFO("TOKEN TYPE: VEC3 \t\t VALUE: vec3");
                break;
            case TokenType::VEC4:
                INFO("TOKEN TYPE: VEC4 \t\t VALUE: vec4");
                break;
            case TokenType::VOID:
                INFO("TOKEN TYPE: VOID \t\t VALUE: void");
                break;
            default:
                INFO("TOKEN TYPE: UNKNOWN  \t VALUE: UNKNOWN");
                break;
        }
    }
}