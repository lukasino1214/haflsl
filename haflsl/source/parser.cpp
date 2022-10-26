#include <haflsl/parser.hpp>
#include <haflsl/lexer.hpp>
#include <haflsl/logger.hpp>
#include <array>

namespace HAFLSL {
    auto Parser::peek(usize advance) -> const Token& {
        if(context->token_index + advance > context->token_count) {
            throw std::runtime_error("ran out of tokens");
        }
		return context->tokens[context->token_index + advance];
    }

    auto Parser::advance() -> const Token& {
        const Token& token = peek();
		context->token_index++;

		return token;
    }

    void Parser::consume(usize count) {
		if(context->token_index + count > context->token_count) {
            throw std::runtime_error("ran out of tokens");
        }
		context->token_index += count;
	}

    auto Parser::is_type(TokenType type) -> bool {
        if(TokenType::BOOL <= type && type <= TokenType::DMAT4X4) {
            return true;
        } else {
            return false;
        }
    }

	auto Parser::expect(const Token& token, TokenType type) -> const Token&{
		if (token.type != type)
            throw std::runtime_error("expecting token");

		return token;
	}

	auto Parser::expect_not(const Token& token, TokenType type) -> const Token& {
		if (token.type == type)
            throw std::runtime_error("unexpected token");

		return token;
	}

	auto Parser::expect(TokenType type) -> const Token& {
		const Token& token = peek();
		expect(token, type);

		return token;
	}

    void Parser::parse(const std::vector<Token>& tokens) {
        Context context_ {
            .token_count = tokens.size(),
            .token_index = 0,
            .tokens = tokens.data()
        };

        context = &context_;

        std::vector<StatementPtr> statements;
        for(;;) {
            StatementPtr statement = parse_root_statement();

            if(!statement)
                break;

            statements.push_back(std::move(statement));
        }

        auto print_statement = [](StatementPtr& stmt) {
            switch(stmt->get_type()) {
                case StatementType::DeclareStructStatement: 
                    {
                        DeclareStructStatement* struct_stmt = dynamic_cast<DeclareStructStatement*>(stmt.get());
                        std::string info = "\tName: " + std::string{struct_stmt->name} + "\n" + "\tMembers:\n";
                        for(auto& m : struct_stmt->members) {
                            info += "\t\t" + std::string{Lexer::token_to_string_view(m.token)} + " " + std::string{m.name} + "\n";
                        }
                        INFO("\nFound struct: \n{}", info);
                        break;
                    }
                case StatementType::DeclareFunctionStatement:
                    {
                        DeclareFunctionStatement* fn_stmt = dynamic_cast<DeclareFunctionStatement*>(stmt.get());
                        std::string info = "\tName: " + std::string{fn_stmt->name} + "\n" + "\tReturned type: " + std::string{Lexer::token_to_string_view(fn_stmt->returned_type)} + "\n" + "\tParameters:\n";
                        for(auto& p : fn_stmt->parameters) {
                            info += "\t\t" + std::string{Lexer::token_to_string_view(p.token)} + " " + std::string{p.name} + "\n";
                        }
                        INFO("\nFound function: \n{}", info)
                        break;
                    }
                default:
                    INFO("wtf");
            }
        };

        for(auto& stmt : statements) {
            print_statement(stmt);
        }
    }

    auto Parser::parse_root_statement() -> StatementPtr {
        const Token& next_token = peek();
        std::vector<std::string_view> structs;

        switch(next_token.type) {
            case TokenType::CONST:
                break;
            case TokenType::STRUCT:
                return parse_struct_declaration();
                break;
            default:
                /*if(is_type(next_token.type) || TokenType::TYPE_NAME == next_token.type) {
                    if(TokenType::IDENTIFIER == peek(1).type) {
                        if(TokenType::LEFT_PAREN == peek(2).type) {
                            INFO("found function")
                        } else if(TokenType::EQUAL == peek(2).type) {
                            INFO("found variable")
                        } else {

                        }
                    }
                    INFO("GOT TYPE: {}", std::get<std::string_view>(next_token.data))
                }*/
                if(is_type(next_token.type) || TokenType::TYPE_NAME == next_token.type) {
                    expect(peek(1), TokenType::IDENTIFIER);
                    if(peek(2).type == TokenType::LEFT_PAREN) {
                        return parse_function_declaration();
                    } else if(peek(2).type == TokenType::EQUAL) {

                    } else {
                        throw std::runtime_error("unexpected token");
                    }
                }
                break;

        }
        // consume();
        return {};
    }

    auto Parser::parse_struct_declaration() -> StatementPtr {
        expect(advance(), TokenType::STRUCT);
        const Token& name_token = expect(advance(), TokenType::IDENTIFIER);
        expect(advance(), TokenType::LEFT_BRACE);

        std::vector<StructMember> members;
        bool first = true;
        for(;;) {
            const Token& token = advance();
            if(first) {
                expect_not(token, TokenType::RIGHT_BRACE);
            }

            first = false;

            if(is_type(token.type)) {
                const Token& variable_name = expect(advance(), TokenType::IDENTIFIER);
                expect(advance(), TokenType::SEMICOLON);

                members.push_back({token, std::get<std::string_view>(variable_name.data)});
                continue;
            }

            if(TokenType::RIGHT_BRACE == token.type) {
                break;
            }

            throw std::runtime_error("unexpected token");
        }
        expect(advance(), TokenType::SEMICOLON);

        auto stmt = std::make_unique<DeclareStructStatement>();
        stmt->name = std::get<std::string_view>(name_token.data);
        stmt->members = std::move(members);

        return stmt;
    }

    auto Parser::parse_function_declaration() -> StatementPtr {
        auto stmt = std::make_unique<DeclareFunctionStatement>();
        stmt->returned_type = advance();
        stmt->name = std::get<std::string_view>(advance().data);
        expect(advance(), TokenType::LEFT_PAREN);

        std::vector<Parameter> parameters;
        for(;;) {
            const Token& type = advance();
            if(is_type(type.type) || TokenType::TYPE_NAME == type.type) {
                const Token& name = expect(advance(), TokenType::IDENTIFIER);
                parameters.push_back({type, std::get<std::string_view>(name.data)});
            } else {
                throw std::runtime_error("unexpected token");
            }

            const Token& token = advance();
            if(TokenType::COMMA == token.type) {
                continue;
            } else if(TokenType::RIGHT_PAREN == token.type) {
                break;
            } else {
                throw std::runtime_error("unexpected token");
            }
        }

        stmt->parameters = std::move(parameters);
        expect(advance(), TokenType::LEFT_BRACE);
        for(;;) {
            const Token& token = advance();

            //TODO: parse statements


            if(TokenType::RIGHT_BRACE == token.type) {
                break;
            }
        }

        return stmt;
    }
}