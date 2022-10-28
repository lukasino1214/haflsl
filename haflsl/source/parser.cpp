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

    auto Parser::is_constant(TokenType type) -> bool {
        if(TokenType::FLOATCONSTANT <= type && type <= TokenType::DOUBLECONSTANT) {
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

        std::function<std::string(ExpressionPtr& expr)> expression_to_string;
        expression_to_string = [&expression_to_string](ExpressionPtr& expr) -> std::string {
            switch(expr->get_type()) {
                case ExpressionType::ConstantValueExpression:
                    {
                        ConstantValueExpression* const_val = dynamic_cast<ConstantValueExpression*>(expr.get());
                        switch(const_val->token.type) {
                            case TokenType::FLOATCONSTANT:
                                return std::to_string(std::get<f64>(const_val->token.data));
                            case TokenType::INTCONSTANT:
                                return std::to_string(std::get<i64>(const_val->token.data));
                            case TokenType::UINTCONSTANT:
                                return std::to_string(std::get<u64>(const_val->token.data));
                            case TokenType::BOOLCONSTANT:
                                return std::get<bool>(const_val->token.data) ? "true": "false";
                            case TokenType::DOUBLECONSTANT:
                                return std::to_string(std::get<f64>(const_val->token.data));
                            default:
                                return "wtf";
                        }
                        break;
                    }
                case ExpressionType::BinaryExpression:
                    {
                        BinaryExpression* bin = dynamic_cast<BinaryExpression*>(expr.get());
                        std::string info = expression_to_string(bin->left);
                        switch(bin->type) {
                            case BinaryType::Multiply:      info += " * ";  break;
                            case BinaryType::Divide:        info += " / ";  break;
                            case BinaryType::Modulo:        info += " % ";  break;
                            case BinaryType::Add:           info += " + ";  break;
                            case BinaryType::Subtract:      info += " - ";  break;
                            case BinaryType::BitShiftLeft:  info += " << "; break;
                            case BinaryType::BitShiftRight: info += " >> "; break;
                            case BinaryType::CompLt:        info += " < ";  break;
                            case BinaryType::CompGt:        info += " > ";  break;
                            case BinaryType::CompLe:        info += " <=";  break;
                            case BinaryType::CompGe:        info += " >= "; break;
                            case BinaryType::CompEq:        info += " == "; break;
                            case BinaryType::CompNe:        info += " != "; break;
                            case BinaryType::BitAnd:        info += " & ";  break;
                            case BinaryType::BitExOr:       info += " ^ ";  break;
                            case BinaryType::BitInOr:       info += " | ";  break;
                            case BinaryType::LogicalAnd:    info += " && "; break;
                            case BinaryType::LogicalOr:     info += " || "; break;
                            default:                        info += "wtf";  break;
                        }
                        info += expression_to_string(bin->right);
                        return info;
                    }
                default:
                    return "wtf";
                    break;
            }
        };

        auto print_statement = [&](StatementPtr& stmt) {
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
                case StatementType::DeclareVariableStatement:
                    {
                        DeclareVariableStatement* var_stmt = dynamic_cast<DeclareVariableStatement*>(stmt.get());
                        std::string info = "\tName: " + std::string{var_stmt->name} + "\n" + "\tType: " + std::string{Lexer::token_to_string_view(var_stmt->type)} +"\n";
                        info += "\tExpr: " + expression_to_string(var_stmt->expression);
                        INFO("\nFound variable: \n{}", info)
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
            case TokenType::EOS:
                return {};
            default:
                if(is_type(next_token.type)) {
                    expect(peek(1), TokenType::IDENTIFIER);
                    if(peek(2).type == TokenType::LEFT_PAREN) {
                        return parse_function_declaration();
                    } else if(peek(2).type == TokenType::EQUAL) {
                        return parse_variable_declaration();
                    } else {
                        throw std::runtime_error("unexpected token");
                    }
                }
                throw std::runtime_error("struct token");
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

    auto Parser::parse_statement_list() -> std::vector<StatementPtr> {
        expect(advance(), TokenType::LEFT_BRACE);
        std::vector<StatementPtr> statements;
        for(;;) {
            if(TokenType::RIGHT_BRACE == peek().type) {
                break;
            }
            statements.push_back(std::move(parse_statement()));
        }
        expect(advance(), TokenType::RIGHT_BRACE);
        return statements;
    }

    auto Parser::parse_single_statement() -> StatementPtr {
        StatementPtr statement;
        while(!statement) {
            const Token& token = peek();
            switch(token.type) {
                case TokenType::WHILE:
                    statement = parse_while_statement();
                    break;
                case TokenType::IF:
                    statement = parse_branch_statement();
                    break;
                case TokenType::DO:
                    //statement = parse_do_statement();
                    break;
                case TokenType::FOR:
                    statement = parse_for_statement();
                    break;
                case TokenType::BREAK:
                    statement = parse_break_statement();
                    break;
                case TokenType::CONTINUE:
                    statement = parse_continue_statement();
                    break;
                case TokenType::RETURN:
                    statement = parse_return_statement();
                    break;
                case TokenType::DISCARD:
                    statement = parse_discard_statement();
                    break;
                case TokenType::CONST:
                    //statement = parse_const_statement();
                    break;
                case TokenType::IDENTIFIER:
                    {
                        auto expr_stmt = std::make_unique<ExpressionStatement>();
                        expr_stmt->expression = parse_expression_statement();
                        expect(advance(), TokenType::SEMICOLON);
                        statement = std::move(expr_stmt);
                        break;
                    }
                case TokenType::LEFT_BRACE:
                    statement = parse_statement();
                    break;
                default:
                    throw std::runtime_error("bozo");
            } 
        };
        return statement;
    }

    auto Parser::parse_discard_statement() -> StatementPtr {
        expect(advance(), TokenType::DISCARD);
        expect(advance(), TokenType::SEMICOLON);
        return std::make_unique<DiscardStatement>();
    }

    auto Parser::parse_return_statement() -> StatementPtr {
        expect(advance(), TokenType::RETURN);

        ExpressionPtr expr;
        if(TokenType::SEMICOLON != peek().type) {
            expr = parse_expression();
        }
        expect(advance(), TokenType::SEMICOLON);
        auto stmt = std::make_unique<ReturnStatement>();
        stmt->expr = std::move(expr);
        return stmt;
    }

    auto Parser::parse_continue_statement() -> StatementPtr {
        expect(advance(), TokenType::CONTINUE);
        expect(advance(), TokenType::SEMICOLON);
        return std::make_unique<ContinueStatement>();
    }

    auto Parser::parse_break_statement() -> StatementPtr {
        expect(advance(), TokenType::BREAK);
        expect(advance(), TokenType::SEMICOLON);
        return std::make_unique<BreakStatement>();
    }

    auto Parser::parse_branch_statement() -> StatementPtr {
        auto stmt = std::make_unique<BranchStatement>();
        bool first = true;
        for(;;) {
            if(!first) {
                expect(advance(), TokenType::ELSE);
            }

            expect(advance(), TokenType::IF);
            first = false;
            auto& cond_stmt = stmt->conditional_statements.emplace_back();
            expect(advance(), TokenType::LEFT_PAREN);
            cond_stmt.condition = parse_expression();
            expect(advance(), TokenType::RIGHT_PAREN);

            cond_stmt.statement = parse_statement();

            if(TokenType::ELSE != peek().type || TokenType::IF != peek(1).type) {
                break;
            }
        }

        if(TokenType::ELSE == peek().type) {
            stmt->else_statement = parse_statement();
        }

        return stmt;
    }

    auto Parser::parse_while_statement() -> StatementPtr {
        expect(advance(), TokenType::WHILE);

        expect(advance(), TokenType::LEFT_PAREN);
        ExpressionPtr expr = parse_expression();
        expect(advance(), TokenType::RIGHT_PAREN);

        StatementPtr body = parse_statement();

        auto stmt = std::make_unique<WhileStatement>();
        stmt->condition = std::move(expr);
        stmt->statement = std::move(body);
        return stmt;
    }

    auto Parser::parse_for_statement() -> StatementPtr {
        expect(advance(), TokenType::FOR);
        expect(advance(), TokenType::LEFT_PAREN);
        StatementPtr var = parse_variable_declaration();
        ExpressionPtr cond = parse_expression();
        expect(advance(), TokenType::SEMICOLON);
        ExpressionPtr step = parse_expression();
        expect(advance(), TokenType::RIGHT_PAREN);
        StatementPtr body = parse_statement();

        auto stmt = std::make_unique<ForStatement>();
        stmt->iterable = std::move(var);
        stmt->condition = std::move(cond);
        stmt->step = std::move(step);
        stmt->statement = std::move(body);
        return stmt;
    }

    auto Parser::parse_statement() -> StatementPtr {
        if(TokenType::LEFT_BRACE == peek().type) {
            auto multi_stmt = std::make_unique<MultiStatement>();
            multi_stmt->statements = parse_statement_list();

            auto stmt = std::make_unique<ScopedStatement>();
            stmt->statement = std::move(multi_stmt);
            return stmt;
        } else {
            return parse_single_statement();
        }
    }
    
    auto Parser::parse_variable_declaration() -> StatementPtr {
        auto stmt = std::make_unique<DeclareVariableStatement>();
        if(is_type(peek().type)) {
            stmt->type = advance();
        } else {
            throw std::runtime_error("cringe");
        }
        const Token& name_token = expect(advance(), TokenType::IDENTIFIER);
        stmt->name = std::get<std::string_view>(name_token.data);
        expect(advance(), TokenType::EQUAL);
        stmt->expression = parse_expression();
        expect(advance(), TokenType::SEMICOLON);
        return stmt;
    }

    auto Parser::parse_expression() -> ExpressionPtr {
        return parse_bin_op_rhs(0, parse_primary_expression());
    }

    auto Parser::parse_bin_op_rhs(i32 expr_precedence, ExpressionPtr lhs) -> ExpressionPtr {
        for(;;) {
            const Token& token = peek();
            TokenType current_token_type = token.type;
            i32 current_token_precedence = get_token_precedence(current_token_type);
            if(current_token_precedence < expr_precedence) {
                return lhs;
            }

            // this only happens when identifier has after parenthesis
            if(TokenType::LEFT_PAREN == current_token_type) {
                consume();
                auto parameters = parse_expression_list();
                auto expr = std::make_unique<CallFunctionExpression>();
                expr->function_expr = std::move(lhs);
                expr->parameters = std::move(parameters);
                lhs = std::move(expr);
                continue;
            }

            consume();
            ExpressionPtr rhs = parse_primary_expression();
            const Token& next_token = peek();
            i32 next_token_precedence = get_token_precedence(next_token.type);
            if (current_token_precedence < next_token_precedence)
                rhs = parse_bin_op_rhs(current_token_precedence - 1, std::move(rhs));

            lhs = [&]{
                switch(current_token_type) {
                    //case TokenType::DOT:            return std::make_unique<Expression>(); // TODO: field
                    case TokenType::STAR:           { auto expr = std::make_unique<BinaryExpression>(); expr->type = BinaryType::Multiply; expr->left = std::move(lhs); expr->right = std::move(rhs);  return expr;}
                    case TokenType::SLASH:          { auto expr = std::make_unique<BinaryExpression>(); expr->type = BinaryType::Divide; expr->left = std::move(lhs); expr->right = std::move(rhs);  return expr;}
                    case TokenType::PERCENT:        { auto expr = std::make_unique<BinaryExpression>(); expr->type = BinaryType::Modulo; expr->left = std::move(lhs); expr->right = std::move(rhs);  return expr;}
                    case TokenType::PLUS:           { auto expr = std::make_unique<BinaryExpression>(); expr->type = BinaryType::Add; expr->left = std::move(lhs); expr->right = std::move(rhs);  return expr;}
                    case TokenType::DASH:           { auto expr = std::make_unique<BinaryExpression>(); expr->type = BinaryType::Subtract; expr->left = std::move(lhs); expr->right = std::move(rhs);  return expr;}
                    case TokenType::LEFT_OP:        { auto expr = std::make_unique<BinaryExpression>(); expr->type = BinaryType::BitShiftLeft; expr->left = std::move(lhs); expr->right = std::move(rhs);  return expr;}
                    case TokenType::RIGHT_OP:       { auto expr = std::make_unique<BinaryExpression>(); expr->type = BinaryType::BitShiftRight; expr->left = std::move(lhs); expr->right = std::move(rhs);  return expr;}
                    case TokenType::LEFT_ANGLE:     { auto expr = std::make_unique<BinaryExpression>(); expr->type = BinaryType::CompLt; expr->left = std::move(lhs); expr->right = std::move(rhs);  return expr;}
                    case TokenType::RIGHT_ANGLE:    { auto expr = std::make_unique<BinaryExpression>(); expr->type = BinaryType::CompGt; expr->left = std::move(lhs); expr->right = std::move(rhs);  return expr;}
                    case TokenType::LE_OP:          { auto expr = std::make_unique<BinaryExpression>(); expr->type = BinaryType::CompLe; expr->left = std::move(lhs); expr->right = std::move(rhs);  return expr;}
                    case TokenType::GE_OP:          { auto expr = std::make_unique<BinaryExpression>(); expr->type = BinaryType::CompGe; expr->left = std::move(lhs); expr->right = std::move(rhs);  return expr;}
                    case TokenType::EQ_OP:          { auto expr = std::make_unique<BinaryExpression>(); expr->type = BinaryType::CompEq; expr->left = std::move(lhs); expr->right = std::move(rhs);  return expr;}
                    case TokenType::NE_OP:          { auto expr = std::make_unique<BinaryExpression>(); expr->type = BinaryType::CompNe; expr->left = std::move(lhs); expr->right = std::move(rhs);  return expr;}
                    case TokenType::AMPERSAND:      { auto expr = std::make_unique<BinaryExpression>(); expr->type = BinaryType::BitAnd; expr->left = std::move(lhs); expr->right = std::move(rhs);  return expr;}
                    case TokenType::CARET:          { auto expr = std::make_unique<BinaryExpression>(); expr->type = BinaryType::BitExOr; expr->left = std::move(lhs); expr->right = std::move(rhs);  return expr;}
                    case TokenType::VERTICAL_BAR:   { auto expr = std::make_unique<BinaryExpression>(); expr->type = BinaryType::BitInOr; expr->left = std::move(lhs); expr->right = std::move(rhs);  return expr;}
                    case TokenType::AND_OP:         { auto expr = std::make_unique<BinaryExpression>(); expr->type = BinaryType::LogicalAnd; expr->left = std::move(lhs); expr->right = std::move(rhs);  return expr;}
                    case TokenType::OR_OP:          { auto expr = std::make_unique<BinaryExpression>(); expr->type = BinaryType::LogicalOr; expr->left = std::move(lhs); expr->right = std::move(rhs);  return expr;}
                    default:
                        throw std::runtime_error("bozo");
                }
            }();
        }
        return {};
    }

    auto Parser::parse_expression_list() -> std::vector<ExpressionPtr> {
        std::vector<ExpressionPtr> parameters;
        bool first = true;
        while(peek().type != TokenType::RIGHT_PAREN) {
            if(!first) {
                expect(advance(), TokenType::COMMA);
            }
            first = false;
            parameters.push_back(parse_expression());
        }
        expect(advance(), TokenType::RIGHT_PAREN);

        return parameters;
    }

    auto Parser::get_token_precedence(const TokenType& token) -> i32 {
        switch(token) {
            case TokenType::LEFT_PAREN:     return 100;
            case TokenType::STAR:           return 200;
            case TokenType::SLASH:          return 200;
            case TokenType::PERCENT:        return 200;
            case TokenType::PLUS:           return 300;
            case TokenType::DASH:           return 300;
            case TokenType::LEFT_OP:        return 400;
            case TokenType::RIGHT_OP:       return 400;
            case TokenType::LEFT_ANGLE:     return 500;
            case TokenType::RIGHT_ANGLE:    return 500;
            case TokenType::LE_OP:          return 500;
            case TokenType::GE_OP:          return 500;
            case TokenType::EQ_OP:          return 600;
            case TokenType::NE_OP:          return 600;
            case TokenType::AMPERSAND:      return 700;
            case TokenType::CARET:          return 800;
            case TokenType::VERTICAL_BAR:   return 900;
            case TokenType::AND_OP:         return 1000;
            case TokenType::OR_OP:          return 1100;
            default: return -1;
        }
        return -1;
    }

    auto Parser::parse_primary_expression() -> ExpressionPtr {
        const Token& token = peek();
        ExpressionPtr primary_expr;
        switch (token.type) {
            case TokenType::PLUS:
            {
                consume();
                ExpressionPtr expr = parse_expression();
                auto minus_expr = std::make_unique<UnaryExpression>();
                minus_expr->type = UnaryType::Plus;
                minus_expr->expr = std::move(expr);
                primary_expr = std::move(minus_expr);
                break;
            }
            case TokenType::DASH:
            {
                consume();
                ExpressionPtr expr = parse_expression();
                auto minus_expr = std::make_unique<UnaryExpression>();
                minus_expr->type = UnaryType::Minus;
                minus_expr->expr = std::move(expr);
                primary_expr = std::move(minus_expr);
                break;
            }
            case TokenType::BANG:
            {
                consume();
                ExpressionPtr expr = parse_expression();
                auto minus_expr = std::make_unique<UnaryExpression>();
                minus_expr->type = UnaryType::LogicalNot;
                minus_expr->expr = std::move(expr);
                primary_expr = std::move(minus_expr);
                break;
            }
            case TokenType::LEFT_PAREN:
				primary_expr = parse_parenthesis_expression();
				break;
            case TokenType::IDENTIFIER:
                primary_expr = parse_constant_expression();
                break;
        default:
            if(is_constant(token.type)) {
                primary_expr = parse_constant_expression();
                break;
            }

            throw std::runtime_error("error bozo");
            break;
        }
        return primary_expr;
    }

    auto Parser::parse_constant_expression() -> ExpressionPtr {
        const Token& token = advance();
        auto expr = std::make_unique<ConstantValueExpression>();
        expr->token = token;
        return expr;
    }

    auto Parser::parse_parenthesis_expression() -> ExpressionPtr {
        expect(advance(), TokenType::LEFT_PAREN);
        ExpressionPtr expr = parse_expression();
        expect(advance(), TokenType::RIGHT_PAREN);
        return expr;
    }

    auto Parser::parse_identifier_expression() -> ExpressionPtr {
        const Token& token = expect(advance(), TokenType::IDENTIFIER);
        auto expr = std::make_unique<IdentifierExpression>();
        expr->name = std::get<std::string_view>(token.data);
        return expr;
    }

    auto Parser::parse_expression_statement() -> ExpressionPtr {
        ExpressionPtr left = parse_expression();
		AssignType assign_type;
		const Token& token = peek();

		switch (token.type) {
            case TokenType::EQUAL:          assign_type = AssignType::Simple;                   break;
            case TokenType::ADD_ASSIGN:     assign_type = AssignType::CompoundAdd;              break;
            case TokenType::SUB_ASSIGN:     assign_type = AssignType::CompoundSubtract;         break;
            case TokenType::MUL_ASSIGN:     assign_type = AssignType::CompoundMultiply;         break;
            case TokenType::DIV_ASSIGN:     assign_type = AssignType::CompoundDivide;           break;
            case TokenType::MOD_ASSIGN:     assign_type = AssignType::CompoundModulo;           break;
            case TokenType::LEFT_ASSIGN:    assign_type = AssignType::CompoundBitShiftLeft;     break;
            case TokenType::RIGHT_ASSIGN:   assign_type = AssignType::CompoundBitShiftRight;    break;
            case TokenType::AND_ASSIGN:     assign_type = AssignType::CompoundBitAnd;           break;
            case TokenType::XOR_ASSIGN:     assign_type = AssignType::CompoundBitExOr;          break;
            case TokenType::OR_ASSIGN:      assign_type = AssignType::CompoundBitInOr;          break;
			case TokenType::SEMICOLON:
				return left;

			default:
				throw std::runtime_error("bozo");
		}

		consume();
		ExpressionPtr right = parse_expression();

		auto expr = std::make_unique<AssignExpression>();
        expr->type = assign_type;
        expr->left = std::move(left);
        expr->right = std::move(right);
		return expr;
    }
}