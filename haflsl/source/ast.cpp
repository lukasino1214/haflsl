#include <haflsl/ast.hpp>
#include <haflsl/lexer.hpp>
#include <haflsl/logger.hpp>
#include <array>

namespace HAFLSL {
    constexpr static std::array<TokenType, 3> types = { TokenType::VEC3, TokenType::VEC4, TokenType::VOID };

    void AST::process(const std::vector<Token>& tokens, const std::string& src) {
        for(u32 i = 0; i < tokens.size(); i++) {
            for(auto& type : types) {
                if(tokens[i].type == type) {
                    if(tokens[i+1].type == TokenType::IDENTIFIER) {
                        if(tokens[i+2].type == TokenType::EQUAL) {
                            INFO("found assignment");
                            u32 start = tokens[i].index;
                            for(u32 j = i + 2; j < tokens.size(); j++) {
                                if(tokens[j].type == TokenType::SEMICOLON) {
                                    std::string_view line(src.data() + start, tokens[j].index - start + 1);
                                    INFO("{}", line);
                                    break;
                                }
                            }
                        }

                        if(tokens[i+2].type == TokenType::LEFT_PAREN) {
                            INFO("found function");
                            u32 start = tokens[i].index;
                            for(u32 j = i + 2; j < tokens.size(); j++) {
                                if(tokens[j].type == TokenType::RIGHT_BRACE) {
                                    std::string_view line(src.data() + start, tokens[j].index - start + 1);
                                    INFO("\n{}", line);
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}