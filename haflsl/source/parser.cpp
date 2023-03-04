#include "haflsl/nodes.hpp"
#include "haflsl/token.hpp"
#include <haflsl/parser.hpp>
#include <haflsl/lexer.hpp>
#include <haflsl/logger.hpp>
#include <array>
#include <string>
#include <string_view>

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
        if(TokenType::BOOL <= type && type <= TokenType::DMAT4X4 || type == TokenType::VOID) {
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

    auto Parser::parse(const std::vector<Token>& tokens) -> AST {
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

        return {std::move(statements)};
    }

    void Parser::print_debug_ast(const AST& ast) {
        auto tabs = [](u32 count) -> std::string {
            std::string str;
            for(u32 i = 0; i < count; i++) {
                str += "    ";
            }
            return str; 
        };

        std::function<std::string(const ExpressionPtr& expr, u32 depth)> expr_to_string;
        expr_to_string = [&tabs, &expr_to_string](const ExpressionPtr& expr, u32 depth) -> std::string {
            switch(expr->get_type()) {
                case ExpressionType::ConstantValueExpression:
                    {
                        ConstantValueExpression* value_expr = dynamic_cast<ConstantValueExpression*>(expr.get());
                        std::string value;
                        switch(value_expr->token.type) {
                            case TokenType::FLOATCONSTANT:
                                value = std::to_string(std::get<f64>(value_expr->token.data));
                                break;
                            case TokenType::INTCONSTANT:
                                value = std::to_string(std::get<i64>(value_expr->token.data));
                                break;
                            case TokenType::UINTCONSTANT:
                                value = std::to_string(std::get<u64>(value_expr->token.data));
                                break;
                            case TokenType::BOOLCONSTANT:
                                value = std::get<bool>(value_expr->token.data) ? "true": "false";
                                break;
                            case TokenType::DOUBLECONSTANT:
                                value = std::to_string(std::get<f64>(value_expr->token.data));
                                break;
                            case TokenType::IDENTIFIER:
                                value = std::string{std::get<std::string_view>(value_expr->token.data)};
                                break;
                            default:
                                value = "wtf";
                                break;
                        }

                        return tabs(depth) + "ConstantValueExpression\n" 
                            + tabs(depth+1) + "Type: " + std::string{Lexer::token_to_string_view(value_expr->token)} + "\n"
                            + tabs(depth+1) + "Value: " + value + "\n";
                    }
                case ExpressionType::BinaryExpression:
                    {
                        BinaryExpression* bin_expr = dynamic_cast<BinaryExpression*>(expr.get());
                        std::string sign;
                        switch(bin_expr->type) {
                            case BinaryType::Multiply:      sign += "*";  break;
                            case BinaryType::Divide:        sign += "/";  break;
                            case BinaryType::Modulo:        sign += "%";  break;
                            case BinaryType::Add:           sign += "+";  break;
                            case BinaryType::Subtract:      sign += "-";  break;
                            case BinaryType::BitShiftLeft:  sign += "<<"; break;
                            case BinaryType::BitShiftRight: sign += ">>"; break;
                            case BinaryType::CompLt:        sign += "<";  break;
                            case BinaryType::CompGt:        sign += ">";  break;
                            case BinaryType::CompLe:        sign += "<="; break;
                            case BinaryType::CompGe:        sign += ">="; break;
                            case BinaryType::CompEq:        sign += "=="; break;
                            case BinaryType::CompNe:        sign += "!="; break;
                            case BinaryType::BitAnd:        sign += "&";  break;
                            case BinaryType::BitExOr:       sign += "^";  break;
                            case BinaryType::BitInOr:       sign += "|";  break;
                            case BinaryType::LogicalAnd:    sign += "&&"; break;
                            case BinaryType::LogicalOr:     sign += "||"; break;
                            default:                        sign += "wtf";  break;
                        }
                        return tabs(depth) + "BinaryExpression\n" 
                            + expr_to_string(bin_expr->left, depth + 1) 
                            + tabs(depth+1) + "Operator: " + sign + "\n" 
                            + expr_to_string(bin_expr->right, depth + 1) +  "\n";
                    }
                    break;
                case ExpressionType::UnaryExpression:
                    {
                        UnaryExpression* unary_expr = dynamic_cast<UnaryExpression*>(expr.get());
                        std::string unary_type;
                        switch(unary_expr->type) {
                            case UnaryType::LogicalNot:      unary_type += "!";  break;
                            case UnaryType::Minus:        unary_type += "-";  break;
                            case UnaryType::Plus:        unary_type += "+";  break;
                            default:                        unary_type += "wtf";  break;
                        }
                        return tabs(depth) + "UnaryExpression\n"
                        + tabs(depth+1) + "Operator: " + unary_type + "\n"
                        + expr_to_string(unary_expr->expr, depth + 1) +  "\n";
                    }
                case ExpressionType::IdentifierExpression:
                    {
                        IdentifierExpression* id_expr = dynamic_cast<IdentifierExpression*>(expr.get());

                        return tabs(depth) + "IdentifierExpression\n"
                            + tabs(depth+1) + "Name: " + std::string{id_expr->name} + "\n";
                    }
                case ExpressionType::AccessIdentifierExpression:
                    return "TODO AccessIdentifierExpression";
                case ExpressionType::AccessIndexExpression:
                    return "TODO AccessIndexExpression";
                case ExpressionType::AssignExpression:
                    {
                        AssignExpression* as_expr = dynamic_cast<AssignExpression*>(expr.get());
                        std::string assign_type;
                        switch(as_expr->type) {
                            case AssignType::Simple:                assign_type += "=";  break;
                            case AssignType::CompoundAdd:           assign_type += "+=";  break;
                            case AssignType::CompoundSubtract:      assign_type += "-=";  break;
                            case AssignType::CompoundMultiply:      assign_type += "*=";  break;
                            case AssignType::CompoundDivide:        assign_type += "/=";  break;
                            case AssignType::CompoundModulo:        assign_type += "%=";  break;
                            case AssignType::CompoundBitShiftLeft:  assign_type += "<<=";  break;
                            case AssignType::CompoundBitShiftRight: assign_type += ">>=";  break;
                            case AssignType::CompoundBitAnd:        assign_type += "&=";  break;
                            case AssignType::CompoundBitExOr:       assign_type += "^=";  break;
                            case AssignType::CompoundBitInOr:       assign_type += "|=";  break;
                            default:                                assign_type += "wtf";  break;
                        }
                        return tabs(depth) + "AssignExpression\n"
                            + expr_to_string(as_expr->left, depth + 1) 
                            + tabs(depth+1) + "Operator: " + assign_type + "\n" 
                            + expr_to_string(as_expr->right, depth + 1);
                    }
                case ExpressionType::CallFunctionExpression:
                    {
                        CallFunctionExpression* fn_expr = dynamic_cast<CallFunctionExpression*>(expr.get());

                        std::string parameters = fn_expr->parameters.size() == 0 ? " None" : "\n";
                        for(auto& p : fn_expr->parameters) {
                            parameters += expr_to_string(p, depth + 2);
                        }

                        return tabs(depth) + "CallFunctionExpression\n"
                        + tabs(depth+1) + "Function Expr: \n" + expr_to_string(fn_expr->function_expr, depth + 2)
                        + tabs(depth+1) + "Paramaters:" + parameters;
                    }
                    break;
                case ExpressionType::ConstructorExpression:
                    {
                        ConstructorExpression* constructor_expr = dynamic_cast<ConstructorExpression*>(expr.get());

                        std::string parameters = constructor_expr->values.size() == 0 ? " None" : "\n";
                        for(auto& p : constructor_expr->values) {
                            parameters += expr_to_string(p, depth + 2);
                        }

                        return tabs(depth) + "ConstructorExpression\n"
                        + tabs(depth+1) + "Type: " + std::string{Lexer::token_to_string_view(constructor_expr->type)} + "\n"
                        + tabs(depth+1) + "Paramaters:" + parameters;
                    }
                    break;
                default:
                    return "wtf";
            }
            return "wtf";
        };

        std::function<std::string(const StatementPtr& stmt, u32 depth)> stmt_to_string;
        stmt_to_string = [&tabs, &expr_to_string, &stmt_to_string](const StatementPtr& stmt, u32 depth) -> std::string {
            switch(stmt->get_type()) {
                case StatementType::BreakStatement:
                    return tabs(depth) + "Break\n";
                case StatementType::ContinueStatement:
                    return tabs(depth) + "Continue\n";
                case StatementType::DiscardStatement:
                    return tabs(depth) + "Discard\n";
                case StatementType::ReturnStatement:
                    {
                        ReturnStatement* return_stmt = dynamic_cast<ReturnStatement*>(stmt.get());
                        return tabs(depth) + "Return\n" 
                            + tabs(depth+1) + "Expression:\n" + expr_to_string(return_stmt->expr, depth+1);
                    }
                case StatementType::DeclareFunctionStatement:
                    {
                        DeclareFunctionStatement* fn_stmt = dynamic_cast<DeclareFunctionStatement*>(stmt.get());
                        
                        std::string parameters;
                        for(auto& p : fn_stmt->parameters) {
                            parameters += "\n" + tabs(depth+2) + "Type: " + std::string{Lexer::token_to_string_view(p.token)} + "\tName: " + std::string{p.name};
                        }

                        std::string statements;
                        for(auto& s : fn_stmt->statements) {
                            statements += stmt_to_string(s, depth+2);
                        }

                        return tabs(depth) + "DeclareFunction\n" 
                            + tabs(depth+1) + "Name: " + std::string{fn_stmt->name} + "\n" 
                            + tabs(depth+1) + "Returned Type: " + std::string{Lexer::token_to_string_view(fn_stmt->returned_type)} + "\n" 
                            + tabs(depth+1) + "Parameters:" + parameters + "\n"
                            + tabs(depth+1) + "Statements:" + "\n" + statements + "\n";
                    }
                case StatementType::DeclareStructStatement:
                    {
                        DeclareStructStatement* struct_stmt = dynamic_cast<DeclareStructStatement*>(stmt.get());

                        std::string members;
                        for(auto& m : struct_stmt->members) {
                            members += "\n" + tabs(depth+2) + "Type: " + std::string{Lexer::token_to_string_view(m.token)} + "\tName: " + std::string{m.name};
                        }

                        return tabs(depth) +"DeclareStruct\n"
                            + tabs(depth+1) + "Name: " + std::string{struct_stmt->name} + "\n"
                            + tabs(depth+1) + "Members: " + members + "\n";
                    }
                case StatementType::DeclareVariableStatement:
                    {
                        DeclareVariableStatement* var_stmt = dynamic_cast<DeclareVariableStatement*>(stmt.get());
                        return tabs(depth) + "DeclareVariable\n"
                            + tabs(depth+1) + "Name: " + std::string{var_stmt->name} + "\n"
                            + tabs(depth+1) + "Type: " + std::string{Lexer::token_to_string_view(var_stmt->type)} + "\n"
                            + tabs(depth+1) + "Expression:\n" + expr_to_string(var_stmt->expression, depth + 2);
                    }
                case StatementType::MultiStatement:
                    {
                        MultiStatement* multi_stmt = dynamic_cast<MultiStatement*>(stmt.get());
                        std::string statements;
                        for(auto& s : multi_stmt->statements) {
                            statements += "\n" + stmt_to_string(s, depth + 2);
                        }
                        return tabs(depth) + "MultiStatement" + statements + "\n";
                    }
                case StatementType::ScopedStatement:
                    {
                        ScopedStatement* scoped_stmt = dynamic_cast<ScopedStatement*>(stmt.get());
                        return tabs(depth) + "ScopedStatement\n" + stmt_to_string(scoped_stmt->statement, depth + 1) + "\n";
                    }
                case StatementType::BranchStatement:
                    return "TODO BranchStatement";
                case StatementType::WhileStatement:
                    return "TODO WhileStatement";
                case StatementType::ForStatement:
                    {
                        ForStatement* for_stmt = dynamic_cast<ForStatement*>(stmt.get());
                        return tabs(depth) +"ForStatement\n" 
                            + tabs(depth+1) + "Iterable: \n" + stmt_to_string(for_stmt->iterable, depth + 2)
                            + tabs(depth+1) + "Condition: \n" + expr_to_string(for_stmt->condition, depth + 2)
                            + tabs(depth+1) + "Step: \n" + expr_to_string(for_stmt->step, depth + 2)
                            + tabs(depth+1) + "Statement: \n" + stmt_to_string(for_stmt->statement, depth + 2);
                    }
                case StatementType::ExpressionStatement:
                    {
                        ExpressionStatement* expr_stmt = dynamic_cast<ExpressionStatement*>(stmt.get());
                        return tabs(depth) + "ExpressionStatement\n" + expr_to_string(expr_stmt->expression, depth + 1);
                    }
                case StatementType::LocationStatement:
                    {
                        LocationStatement* loc_stmt = dynamic_cast<LocationStatement*>(stmt.get());

                        return tabs(depth) +"LocationStatement\n" 
                            + tabs(depth+1) + "Location: " + std::to_string(loc_stmt->location) + "\n"
                            + tabs(depth+1) + "Way: " + std::string{Lexer::token_to_string_view(loc_stmt->way)} + "\n"
                            + tabs(depth+1) + "Type: " + std::string{Lexer::token_to_string_view(loc_stmt->type)} + "\n"
                            + tabs(depth+1) + "Name: " + std::string{loc_stmt->name} + "\n";
                    }
                default:
                    return "";
            }
            return "";
        };

        std::string info;
        for(const auto& stmt : ast.statements) {
            info += stmt_to_string(stmt, 0);     
        }
        

        INFO("printing out AST: \n{}", info);
    }

    auto Parser::parse_root_statement() -> StatementPtr {
        const Token& next_token = peek();
        std::vector<std::string_view> structs;

        switch(next_token.type) {
            case TokenType::CONST:
                break;
            case TokenType::STRUCT:
                return parse_struct_declaration();
            case TokenType::TYPE_NAME:
                return parse_variable_declaration();
            case TokenType::EOS:
                return {};
            case TokenType::IDENTIFIER: 
                {
                    auto expr_stmt = std::make_unique<ExpressionStatement>();
                    expr_stmt->expression = parse_expression_statement();
                    expect(advance(), TokenType::SEMICOLON);
                    return std::move(expr_stmt);
                    break;
                }
            case TokenType::LAYOUT: 
                {
                    return parse_layout_statement();
                }
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
                throw std::runtime_error("unexpected token");
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
            } else if(type.type == TokenType::RIGHT_PAREN) {
                break;
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
        stmt->statements = parse_statement_list();

        return stmt;
    }

    auto Parser::parse_statement_list() -> std::vector<StatementPtr> {
        expect(advance(), TokenType::LEFT_BRACE);
        std::vector<StatementPtr> statements;
        for(;;) {
            if(TokenType::RIGHT_BRACE == peek().type) {
                break;
            }
            statements.push_back(parse_statement());
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
                case TokenType::TYPE_NAME:
                    return parse_variable_declaration();
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
                    if(is_type(token.type)) {
                        expect(peek(1), TokenType::IDENTIFIER);
                        if(peek(2).type == TokenType::EQUAL) {
                            return parse_variable_declaration();
                        } else {
                            throw std::runtime_error("unexpected token");
                        }
                    }

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

    auto Parser::parse_layout_statement() -> StatementPtr {
        expect(advance(), TokenType::LAYOUT);
        expect(advance(), TokenType::LEFT_PAREN);
        expect(advance(), TokenType::LOCATION);
        expect(advance(), TokenType::EQUAL);
        Token location = peek();
        expect(advance(), TokenType::INTCONSTANT);
        expect(advance(), TokenType::RIGHT_PAREN);
        Token way = advance();
        Token type = advance();
        Token name = expect(advance(), TokenType::IDENTIFIER);
        expect(advance(), TokenType::SEMICOLON);

        auto stmt = std::make_unique<LocationStatement>();

        stmt->location = static_cast<u32>(std::get<i64>(location.data));
        stmt->way = way;
        stmt->type = type;
        stmt->name = std::get<std::string_view>(name.data);

        return stmt;
    }

    auto Parser::parse_for_statement() -> StatementPtr {
        expect(advance(), TokenType::FOR);
        expect(advance(), TokenType::LEFT_PAREN);
        StatementPtr var = parse_variable_declaration();
        ExpressionPtr cond = parse_expression();
        expect(advance(), TokenType::SEMICOLON);
        ExpressionPtr step = parse_expression_statement();
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
        if(is_type(peek().type) || TokenType::TYPE_NAME == peek().type) {
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

    auto Parser::parse_constructor_expression() -> ExpressionPtr {
        auto constructor_expr = std::make_unique<ConstructorExpression>();
        //INFO("{}", Lexer::token_to_string_view(peek()));
        constructor_expr->type = advance();
        expect(advance(), TokenType::LEFT_PAREN);
        constructor_expr->values = parse_expression_list();
        return constructor_expr;
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
                    case TokenType::DOT:            return build_identifier_access(std::move(lhs), std::move(rhs));
                    case TokenType::LEFT_BRACKET:   return build_index_access(std::move(lhs), std::move(rhs));
                    case TokenType::STAR:           return build_binary(BinaryType::Multiply, std::move(lhs), std::move(rhs));
                    case TokenType::SLASH:          return build_binary(BinaryType::Divide, std::move(lhs), std::move(rhs));
                    case TokenType::PERCENT:        return build_binary(BinaryType::Modulo, std::move(lhs), std::move(rhs));
                    case TokenType::PLUS:           return build_binary(BinaryType::Add, std::move(lhs), std::move(rhs));
                    case TokenType::DASH:           return build_binary(BinaryType::Subtract, std::move(lhs), std::move(rhs));
                    case TokenType::LEFT_OP:        return build_binary(BinaryType::BitShiftLeft, std::move(lhs), std::move(rhs));
                    case TokenType::RIGHT_OP:       return build_binary(BinaryType::BitShiftRight, std::move(lhs), std::move(rhs));
                    case TokenType::LEFT_ANGLE:     return build_binary(BinaryType::CompLt, std::move(lhs), std::move(rhs));
                    case TokenType::RIGHT_ANGLE:    return build_binary(BinaryType::CompGt, std::move(lhs), std::move(rhs));
                    case TokenType::LE_OP:          return build_binary(BinaryType::CompLe, std::move(lhs), std::move(rhs));
                    case TokenType::GE_OP:          return build_binary(BinaryType::CompGe, std::move(lhs), std::move(rhs));
                    case TokenType::EQ_OP:          return build_binary(BinaryType::CompEq, std::move(lhs), std::move(rhs));
                    case TokenType::NE_OP:          return build_binary(BinaryType::CompNe, std::move(lhs), std::move(rhs));
                    case TokenType::AMPERSAND:      return build_binary(BinaryType::BitAnd, std::move(lhs), std::move(rhs));
                    case TokenType::CARET:          return build_binary(BinaryType::BitExOr, std::move(lhs), std::move(rhs));
                    case TokenType::VERTICAL_BAR:   return build_binary(BinaryType::BitInOr, std::move(lhs), std::move(rhs));
                    case TokenType::AND_OP:         return build_binary(BinaryType::LogicalAnd, std::move(lhs), std::move(rhs));
                    case TokenType::OR_OP:          return build_binary(BinaryType::LogicalOr, std::move(lhs), std::move(rhs));
                    default:
                        throw std::runtime_error("bozo");
                }
            }();
        }
        return {};
    }

    auto Parser::build_identifier_access(ExpressionPtr lhs, ExpressionPtr rhs) -> ExpressionPtr {
        if(ExpressionType::IdentifierExpression == rhs->get_type()) {
            auto expr = std::make_unique<AccessIdentifierExpression>();
            expr->expr = std::move(lhs);
            expr->identifiers.push_back(std::move(dynamic_cast<IdentifierExpression*>(rhs.get())->name));
            return expr;
        } else {
            throw std::runtime_error("error cringe");
        }
    }

    auto Parser::build_index_access(ExpressionPtr lhs, ExpressionPtr rhs) -> ExpressionPtr {
        auto expr = std::make_unique<AccessIndexExpression>();
        expr->expr = std::move(lhs);
        expr->indices.push_back(std::move(rhs));
        expect(advance(), TokenType::RIGHT_BRACKET);
        return expr;
    }
    
    auto Parser::build_binary(BinaryType binary_type, ExpressionPtr lhs, ExpressionPtr rhs) -> ExpressionPtr {
        auto expr = std::make_unique<BinaryExpression>(); 
        expr->type = binary_type; 
        expr->left = std::move(lhs); 
        expr->right = std::move(rhs);  
        return expr;
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
            case TokenType::STAR:           return 80;
            case TokenType::SLASH:          return 80;
            case TokenType::PERCENT:        return 80;
            case TokenType::PLUS:           return 60;
            case TokenType::DASH:           return 60;
            case TokenType::LEFT_OP:        return 30;
            case TokenType::RIGHT_OP:       return 30;
            case TokenType::LEFT_ANGLE:     return 40;
            case TokenType::RIGHT_ANGLE:    return 40;
            case TokenType::LE_OP:          return 40;
            case TokenType::GE_OP:          return 40;
            case TokenType::EQ_OP:          return 50;
            case TokenType::NE_OP:          return 50;
            case TokenType::AMPERSAND:      return 30;
            case TokenType::CARET:          return 30;
            case TokenType::VERTICAL_BAR:   return 30;
            case TokenType::AND_OP:         return 30;
            case TokenType::OR_OP:          return 30;
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

            if(is_type(token.type)) {
                primary_expr = parse_constructor_expression();
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