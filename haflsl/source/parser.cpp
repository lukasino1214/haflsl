#include <haflsl/parser.hpp>

#include <iostream>
#include <functional>

namespace haflsl {
    auto Parser::peek(usize advance) -> const Token & {
        if (context->token_index + advance > context->token_count) {
            throw std::runtime_error("ran out of tokens");
        }
        return context->tokens[context->token_index + advance];
    }

    auto Parser::advance() -> const Token & {
        const Token &token = peek();
        context->token_index++;

        return token;
    }

    void Parser::consume(usize count) {
        if (context->token_index + count > context->token_count) {
            throw std::runtime_error("ran out of tokens");
        }
        context->token_index += count;
    }

    auto Parser::expect(const Token &token, TokenType type) -> const Token & {
        if (token.type != type)
            throw std::runtime_error("expecting token");

        return token;
    }

    auto Parser::expect_not(const Token &token, TokenType type) -> const Token & {
        if (token.type == type)
            throw std::runtime_error("unexpected token");

        return token;
    }

    auto Parser::expect(TokenType type) -> const Token & {
        const Token &token = peek();
        expect(token, type);

        return token;
    }

    auto Parser::is_type(TokenType type) -> bool {
        return static_cast<u32>(type) >= static_cast<u32>(TokenType::BOOL) && static_cast<u32>(type) <= static_cast<u32>(TokenType::IVEC4);
    }

    auto Parser::is_constant(TokenType type) -> bool {
        return static_cast<u32>(type) >= static_cast<u32>(TokenType::BOOL_CONSTANT) && static_cast<u32>(type) <= static_cast<u32>(TokenType::STRING_CONSTANT);
    }

    void Parser::debug_print(const std::vector<StatementPtr> &ast) {
        auto tabs = [](u32 count) -> std::string {
            std::string str;
            for (u32 i = 0; i < count; i++) {
                str += "    ";
            }
            return str;
        };

        std::function<std::string(const ExpressionPtr &expr, u32 depth)> print_expr;
        print_expr = [&print_expr, &tabs](const ExpressionPtr &expr, u32 depth) -> std::string {
            switch (expr->get_type()) {
                case ExpressionType::ConstantValueExpression: {
                    {
                        auto *value_expr = dynamic_cast<ConstantValueExpression *>(expr.get());
                        std::string value;
                        std::string type;
                        switch (value_expr->token.type) {
                            case TokenType::FLOAT_CONSTANT:
                                value = std::to_string(std::get<f64>(value_expr->token.value));
                                type = "FLOAT";
                                break;
                            case TokenType::INT_CONSTANT:
                                value = std::to_string(std::get<i64>(value_expr->token.value));
                                type = "INT";
                                break;
                            case TokenType::BOOL_CONSTANT:
                                value = std::get<bool>(value_expr->token.value) ? "true" : "false";
                                type = "BOOL";
                                break;
                            case TokenType::STRING_CONSTANT:
                                value = std::get<std::string>(value_expr->token.value);
                                type = "STRING";
                                break;
                            case TokenType::IDENTIFIER:
                                value = std::get<std::string>(value_expr->token.value);
                                type = "VARIABLE";
                                break;
                            default:
                                value = "wtf";
                                break;
                        }

                        return tabs(depth) + "ConstantValueExpression\n" + tabs(depth + 1) + "Type: " + type + "\n" + tabs(depth + 1) + "Value: " + value + "\n";
                        break;
                    }
                    case ExpressionType::UnaryExpression: {
                        auto *unary_expr = dynamic_cast<UnaryExpression *>(expr.get());
                        std::string unary_type;
                        switch (unary_expr->type) {
                            case UnaryType::LogicalNot: unary_type += "!"; break;
                            case UnaryType::Minus: unary_type += "-"; break;
                            case UnaryType::Plus: unary_type += "+"; break;
                            default: unary_type += "wtf"; break;
                        }
                        return tabs(depth) + "UnaryExpression\n" + tabs(depth + 1) + "Operator: " + unary_type + "\n" + print_expr(unary_expr->expr, depth + 1);
                    }
                    case ExpressionType::BinaryExpression: {
                        auto *bin_expr = dynamic_cast<BinaryExpression *>(expr.get());
                        std::string sign;
                        switch (bin_expr->type) {
                            case BinaryType::Multiply: sign += "*"; break;
                            case BinaryType::Divide: sign += "/"; break;
                            case BinaryType::Modulo: sign += "%"; break;
                            case BinaryType::Add: sign += "+"; break;
                            case BinaryType::Subtract: sign += "-"; break;
                            case BinaryType::BitShiftLeft: sign += "<<"; break;
                            case BinaryType::BitShiftRight: sign += ">>"; break;
                            case BinaryType::CompLt: sign += "<"; break;
                            case BinaryType::CompGt: sign += ">"; break;
                            case BinaryType::CompLe: sign += "<="; break;
                            case BinaryType::CompGe: sign += ">="; break;
                            case BinaryType::CompEq: sign += "=="; break;
                            case BinaryType::CompNe: sign += "!="; break;
                            case BinaryType::BitAnd: sign += "&"; break;
                            case BinaryType::BitExOr: sign += "^"; break;
                            case BinaryType::BitInOr: sign += "|"; break;
                            case BinaryType::LogicalAnd: sign += "&&"; break;
                            case BinaryType::LogicalOr: sign += "||"; break;
                            default: sign += "wtf"; break;
                        }
                        return tabs(depth) + "BinaryExpression:\n" + print_expr(bin_expr->left, depth + 1) + tabs(depth + 1) + "Operator: " + sign + "\n" + print_expr(bin_expr->right, depth + 1);
                    }
                    case ExpressionType::AssignExpression: {
                        AssignExpression *as_expr = dynamic_cast<AssignExpression *>(expr.get());
                        std::string assign_type;
                        switch (as_expr->type) {
                            case AssignType::Simple: assign_type += "="; break;
                            case AssignType::CompoundAdd: assign_type += "+="; break;
                            case AssignType::CompoundSubtract: assign_type += "-="; break;
                            case AssignType::CompoundMultiply: assign_type += "*="; break;
                            case AssignType::CompoundDivide: assign_type += "/="; break;
                            case AssignType::CompoundModulo: assign_type += "%="; break;
                            /*case AssignType::CompoundBitShiftLeft:  assign_type += "<<=";  break;
                            case AssignType::CompoundBitShiftRight: assign_type += ">>=";  break;
                            case AssignType::CompoundBitAnd:        assign_type += "&=";  break;
                            case AssignType::CompoundBitExOr:       assign_type += "^=";  break;
                            case AssignType::CompoundBitInOr:       assign_type += "|=";  break;*/
                            default: assign_type += "wtf"; break;
                        }
                        return tabs(depth) + "AssignExpression\n" + print_expr(as_expr->left, depth + 1) + tabs(depth + 1) + "Operator: " + assign_type + "\n" + print_expr(as_expr->right, depth + 1);
                    }
                    case ExpressionType::CallFunctionExpression: {
                        CallFunctionExpression *fn_expr = dynamic_cast<CallFunctionExpression *>(expr.get());

                        std::string parameters = fn_expr->parameters.size() == 0 ? " None" : "\n";
                        for (auto &p : fn_expr->parameters) {
                            parameters += print_expr(p, depth + 2);
                        }

                        return tabs(depth) + "CallFunctionExpression\n" + tabs(depth + 1) + "Function Expr: \n" + print_expr(fn_expr->function_expr, depth + 2) + tabs(depth + 1) + "Paramaters:" + parameters;
                    }
                    case ExpressionType::AccessIdentifierExpression: {
                        auto *ac_expr = dynamic_cast<AccessIdentifierExpression *>(expr.get());
                        std::string bruh;
                        for (auto &i : ac_expr->identifiers) {
                            bruh += i + "\n";
                        }
                        bruh += print_expr(ac_expr->expr, depth + 1);
                        return tabs(depth) + "AccessIdentifierExpression\n" + tabs(depth + 1) + bruh + "\n";
                    }
                    case ExpressionType::ConstructorExpression: {
                        ConstructorExpression *constructor_expr = dynamic_cast<ConstructorExpression *>(expr.get());

                        std::string parameters = constructor_expr->values.size() == 0 ? " None" : "\n";
                        for (auto &p : constructor_expr->values) {
                            parameters += print_expr(p, depth + 2);
                        }

                        return tabs(depth) + "ConstructorExpression\n" + tabs(depth + 1) + "Type: " + constructor_expr->type.type_to_str() + "\n" + tabs(depth + 1) + "Paramaters:" + parameters;
                    } break;
                    default: {
                        throw std::runtime_error("unhandled expr type in debug print: " + std::string{expr->get_name()});
                    }
                }

                    return "";
            };
        };

        std::function<std::string(const StatementPtr &stmt, u32 depth)> print_stmt;
        print_stmt = [&print_expr, &print_stmt, &tabs](const StatementPtr &stmt, u32 depth) -> std::string {
            switch (stmt->get_type()) {
                case StatementType::PrintStatement: {
                    auto *print_stmt_ = dynamic_cast<PrintStatement *>(stmt.get());
                    return tabs(depth) + "PrintStatement:\n" + tabs(depth + 1) + "Expression:\n" + print_expr(print_stmt_->expression, depth + 2);
                }
                case StatementType::DeclareVariableStatement: {
                    auto *var_stmt = dynamic_cast<DeclareVariableStatement *>(stmt.get());
                    return tabs(depth) + "DeclareVariable:\n" + tabs(depth + 1) + "Name: " + var_stmt->name + "\n" + tabs(depth + 1) + "Type: " + var_stmt->type.type_to_str() + "\n" + tabs(depth + 1) + "Expression:\n" + print_expr(var_stmt->expression, depth + 2);
                }
                case StatementType::DeclareFunctionStatement: {
                    auto *fn_stmt = dynamic_cast<DeclareFunctionStatement *>(stmt.get());

                    std::string parameters;
                    for (auto &p : fn_stmt->parameters) {
                        parameters += "\n" + tabs(depth + 2) + "Type: " + p.token.type_to_str() + "\tName: " + std::string{p.name};
                    }

                    std::string statements;
                    for (auto &s : fn_stmt->statements) {
                        statements += print_stmt(s, depth + 2);
                    }

                    return tabs(depth) + "DeclareFunction\n" + tabs(depth + 1) + "Name: " + std::string{fn_stmt->name} + "\n" + tabs(depth + 1) + "Returned Type: " + fn_stmt->returned_type.type_to_str() + "\n" + tabs(depth + 1) + "Parameters:" + parameters + "\n" + tabs(depth + 1) + "Statements:" + "\n" + statements;
                }
                case StatementType::MultiStatement: {
                    auto *multi_stmt = dynamic_cast<MultiStatement *>(stmt.get());
                    std::string statements;
                    for (auto &s : multi_stmt->statements) {
                        statements += "\n" + print_stmt(s, depth + 2);
                    }
                    return tabs(depth) + "MultiStatement:" + statements + "\n";
                }
                case StatementType::ScopedStatement: {
                    auto *scoped_stmt = dynamic_cast<ScopedStatement *>(stmt.get());
                    return tabs(depth) + "ScopedStatement:\n" + print_stmt(scoped_stmt->statement, depth + 1) + "\n";
                }
                case StatementType::ReturnStatement: {
                    auto *return_stmt = dynamic_cast<ReturnStatement *>(stmt.get());
                    return tabs(depth) + "Return\n" + tabs(depth + 1) + "Expression:\n" + print_expr(return_stmt->expr, depth + 1);
                }
                case StatementType::ExpressionStatement: {
                    ExpressionStatement *expr_stmt = dynamic_cast<ExpressionStatement *>(stmt.get());
                    return tabs(depth) + "ExpressionStatement:\n" + print_expr(expr_stmt->expression, depth + 1);
                }
                case StatementType::BranchStatement: {
                    auto *branch_stmt = dynamic_cast<BranchStatement *>(stmt.get());
                    std::string statements;
                    for (auto &s : branch_stmt->conditional_statements) {
                        statements += tabs(depth + 1) + "Condition:\n" + print_expr(s.condition, depth + 2);
                        statements += tabs(depth + 1) + "Statement:\n" + print_stmt(s.statement, depth + 2);
                    }

                    statements += tabs(depth + 1) + "Else statement:\n" + (branch_stmt->else_statement ? print_stmt(branch_stmt->else_statement, depth + 2) : "");

                    return tabs(depth) + "BranchStatement:" + '\n' + statements + "\n";
                }
                case StatementType::WhileStatement: {
                    auto *while_stmt = dynamic_cast<WhileStatement *>(stmt.get());
                    return tabs(depth) + "WhileStatement:\n" + tabs(depth + 1) + "Condition:\n" + print_expr(while_stmt->condition, depth + 2) + tabs(depth + 1) + "Statement:\n" + print_stmt(while_stmt->statement, depth + 2) + "\n";
                }
                case StatementType::ForStatement: {
                    ForStatement *for_stmt = dynamic_cast<ForStatement *>(stmt.get());
                    return tabs(depth) + "ForStatement\n" + tabs(depth + 1) + "Iterable: \n" + print_stmt(for_stmt->iterable, depth + 2) + tabs(depth + 1) + "Condition: \n" + print_expr(for_stmt->condition, depth + 2) + tabs(depth + 1) + "Step: \n" + print_expr(for_stmt->step, depth + 2) + tabs(depth + 1) + "Statement: \n" + print_stmt(for_stmt->statement, depth + 2);
                }
                case StatementType::DeclareStructStatement: {
                    DeclareStructStatement *struct_stmt = dynamic_cast<DeclareStructStatement *>(stmt.get());

                    /*std::string members;
                    for (auto &m : struct_stmt->members) {
                        members += "\n" + tabs(depth + 2) + "Type: " + std::string{Lexer::token_to_string_view(m.token)} + "\tName: " + std::string{m.name};
                    }*/

                    std::string bruh;
                    for (auto &m : struct_stmt->methods) {
                        bruh += print_stmt(m, depth + 1);
                    }

                    return tabs(depth) + "DeclareStruct\n" + tabs(depth + 1) + "Name: " + std::string{struct_stmt->name} + "\n" + tabs(depth + 1) + "Members: " + bruh + "\n";
                }
                case StatementType::LocationStatement: {
                    auto *loc_stmt = dynamic_cast<LocationStatement *>(stmt.get());

                    return tabs(depth) + "LocationStatement\n" + tabs(depth + 1) + "Location: " + std::to_string(loc_stmt->location) + "\n" + tabs(depth + 1) + "Way: " + loc_stmt->way.type_to_str() + "\n" + tabs(depth + 1) + "Type: " + loc_stmt->type.type_to_str() + "\n" + tabs(depth + 1) + "Name: " + loc_stmt->name + "\n";
                }
                default: {
                    throw std::runtime_error("unhandled stmt type in debug print: " + std::string{stmt->get_name()});
                }
            }

            return "";
        };

        for (auto &stmt : ast) {
            std::cout << print_stmt(stmt, 0) << std::endl;
        }
    }

    auto Parser::parse(const Global &global, std::vector<Token> tokens) -> Result<std::vector<StatementPtr>> {
        Context context_{
            .token_count = tokens.size(),
            .token_index = 0,
            .tokens = tokens.data()};

        context = &context_;

        std::vector<StatementPtr> statements;
        for (;;) {
            StatementPtr statement = parse_root_statement();

            if (!statement) {
                break;
            }

            statements.push_back(std::move(statement));
        }

        return Result<std::vector<StatementPtr>>(std::move(statements));
    }

    auto Parser::parse_root_statement() -> StatementPtr {
        /*switch (peek(0).type) {
            case TokenType::PRINT: {
                return parse_print_statement();
            }
            case TokenType::FUNCTION: {
                return parse_function_declaration();
            }
            case TokenType::IDENTIFIER: {
                auto expr_stmt = std::make_unique<ExpressionStatement>();
                expr_stmt->expression = parse_expression_statement();
                expect(advance(), TokenType::SEMICOLON);
                return std::move(expr_stmt);
                break;
            }
            case TokenType::LEFT_BRACE: {
                auto stmt = parse_statement();
                return std::move(stmt);
                break;
            }
            case TokenType::IF: {
                return parse_branch_statement();
                break;
            }
            case TokenType::EOS: {
                return {};
            }
            default: {
                if (is_type(peek(0).type)) {
                    return parse_variable_declaration();
                }

                throw std::runtime_error("unhandled token in root statement " + peek(0).type_to_str());
                break;
            }
        }*/

        if (is_type(peek(0).type)) {
            return parse_variable_declaration();
        }

        return parse_single_statement();

        return {};
    }

    auto Parser::parse_print_statement() -> StatementPtr {
        expect(advance(), TokenType::PRINT);
        expect(advance(), TokenType::LEFT_PAREN);
        ExpressionPtr expr = parse_expression();
        expect(advance(), TokenType::RIGHT_PAREN);
        expect(advance(), TokenType::SEMICOLON);

        auto stmt = std::make_unique<PrintStatement>();
        stmt->expression = std::move(expr);
        return stmt;
    }

    auto Parser::parse_function_declaration() -> StatementPtr {
        auto stmt = std::make_unique<DeclareFunctionStatement>();
        expect(advance(), TokenType::FUNCTION);
        stmt->name = std::get<std::string>(expect(advance(), TokenType::IDENTIFIER).value);
        expect(advance(), TokenType::LEFT_PAREN);
        std::vector<Parameter> parameters;
        for (;;) {
            const Token &type = advance();
            if (is_type(type.type)) {
                const Token &name = expect(advance(), TokenType::IDENTIFIER);
                parameters.push_back({type, std::get<std::string>(name.value)});
            } else if (type.type == TokenType::RIGHT_PAREN) {
                break;
            } else {
                throw std::runtime_error("unexpected token");
            }

            const Token &token = advance();
            if (TokenType::COMMA == token.type) {
                continue;
            } else if (TokenType::RIGHT_PAREN == token.type) {
                break;
            } else {
                throw std::runtime_error("unexpected token");
            }
        }

        if (peek(0).type == TokenType::ARROW) {
            consume();
            stmt->returned_type = advance();
        } else {
            const Token &token = peek(0);
            stmt->returned_type = {
                .type = TokenType::VOID,
                .line = token.line,
                .column = token.column,
                .value = std::monostate{}};
        }

        stmt->parameters = std::move(parameters);
        stmt->statements = parse_statement_list();

        return stmt;
    }

    auto Parser::parse_statement_list() -> std::vector<StatementPtr> {
        expect(advance(), TokenType::LEFT_BRACE);
        std::vector<StatementPtr> statements;
        for (;;) {
            if (TokenType::RIGHT_BRACE == peek().type) {
                break;
            }
            statements.push_back(parse_statement());
        }
        expect(advance(), TokenType::RIGHT_BRACE);
        return statements;
    }
    auto Parser::parse_single_statement() -> StatementPtr {
        StatementPtr statement;
        while (!statement) {
            const Token &token = peek();
            switch (token.type) {
                case TokenType::PRINT: {
                    statement = parse_print_statement();
                    break;
                }
                case TokenType::RETURN: {
                    statement = parse_return_statement();
                    break;
                }
                case TokenType::FUNCTION: {
                    statement = parse_function_declaration();
                    break;
                }
                case TokenType::LAYOUT: {
                    statement = parse_layout_statement();
                    break;
                }
                case TokenType::IDENTIFIER: {
                    auto expr_stmt = std::make_unique<ExpressionStatement>();
                    expr_stmt->expression = parse_expression_statement();
                    expect(advance(), TokenType::SEMICOLON);
                    statement = std::move(expr_stmt);
                    break;
                }
                case TokenType::LEFT_BRACE: {
                    statement = parse_statement();
                    break;
                }
                case TokenType::IF: {
                    statement = parse_branch_statement();
                    break;
                }
                case TokenType::WHILE: {
                    statement = parse_while_statement();
                    break;
                }
                case TokenType::FOR: {
                    statement = parse_for_statement();
                    break;
                }
                case TokenType::STRUCT: {
                    statement = parse_struct_declaration();
                    break;
                }
                case TokenType::EOS: {
                    return {};
                }
                default: {
                    if (is_type(token.type)) {
                        statement = parse_variable_declaration();
                        break;
                    }
                    throw std::runtime_error("couldnt parse in parse_single_statement()");
                }
            }
        }

        return statement;
    }

    auto Parser::parse_statement() -> StatementPtr {
        if (TokenType::LEFT_BRACE == peek().type) {
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
        if (is_type(peek().type)) {
            stmt->type = advance();
        } else {
            throw std::runtime_error("cringe");
        }
        const Token &name_token = expect(advance(), TokenType::IDENTIFIER);
        stmt->name = std::get<std::string>(name_token.value);
        expect(advance(), TokenType::EQUAL);
        stmt->expression = parse_expression();
        expect(advance(), TokenType::SEMICOLON);
        return stmt;
    }

    auto Parser::parse_return_statement() -> StatementPtr {
        expect(advance(), TokenType::RETURN);

        ExpressionPtr expr;
        if (TokenType::SEMICOLON != peek().type) {
            expr = parse_expression();
        }
        expect(advance(), TokenType::SEMICOLON);
        auto stmt = std::make_unique<ReturnStatement>();
        stmt->expr = std::move(expr);
        return stmt;
    }

    auto Parser::parse_expression_statement() -> ExpressionPtr {
        ExpressionPtr left = parse_expression();
        AssignType assign_type;
        const Token &token = peek();

        switch (token.type) {
            case TokenType::EQUAL: assign_type = AssignType::Simple; break;
            case TokenType::PLUS_ASSIGN: assign_type = AssignType::CompoundAdd; break;
            case TokenType::MINUS_ASSIGN: assign_type = AssignType::CompoundSubtract; break;
            case TokenType::STAR_ASSIGN: assign_type = AssignType::CompoundMultiply; break;
            case TokenType::SLASH_ASSIGN: assign_type = AssignType::CompoundDivide; break;
            case TokenType::MODULO_ASSIGN: assign_type = AssignType::CompoundModulo; break;
            /*case TokenType::LEFT_ASSIGN: assign_type = AssignType::CompoundBitShiftLeft; break;
            case TokenType::RIGHT_ASSIGN: assign_type = AssignType::CompoundBitShiftRight; break;
            case TokenType::AND_ASSIGN: assign_type = AssignType::CompoundBitAnd; break;
            case TokenType::XOR_ASSIGN: assign_type = AssignType::CompoundBitExOr; break;
            case TokenType::OR_ASSIGN: assign_type = AssignType::CompoundBitInOr; break;*/
            case TokenType::SEMICOLON:
                return left;
            default:
                throw std::runtime_error("unhandled token type in expression statement");
        }

        consume();
        ExpressionPtr right = parse_expression();

        auto expr = std::make_unique<AssignExpression>();
        expr->type = assign_type;
        expr->left = std::move(left);
        expr->right = std::move(right);
        return expr;
    }

    auto Parser::parse_branch_statement() -> StatementPtr {
        auto stmt = std::make_unique<BranchStatement>();
        bool first = true;
        for (;;) {
            if (!first) {
                expect(advance(), TokenType::ELSE);
            }

            expect(advance(), TokenType::IF);
            first = false;
            auto &cond_stmt = stmt->conditional_statements.emplace_back();
            expect(advance(), TokenType::LEFT_PAREN);
            cond_stmt.condition = parse_expression();
            expect(advance(), TokenType::RIGHT_PAREN);

            cond_stmt.statement = parse_statement();

            if (TokenType::ELSE != peek().type || TokenType::IF != peek(1).type) {
                break;
            }
        }

        if (TokenType::ELSE == peek().type) {
            consume();
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

    auto Parser::parse_struct_declaration() -> StatementPtr {
        expect(advance(), TokenType::STRUCT);
        const Token &name_token = expect(advance(), TokenType::IDENTIFIER);
        expect(advance(), TokenType::LEFT_BRACE);

        std::vector<StatementPtr> methods;
        bool first = true;
        for (;;) {
            /*const Token &token = peek();


            if (TokenType::RIGHT_BRACE == token.type) {
                break;
            }*/
            const Token &token = peek();

            if (token.type == TokenType::FUNCTION) {
                methods.push_back(parse_function_declaration());
            }

            if (token.type == TokenType::RIGHT_BRACE) {
                break;
            }

            // token.print();
        }
        expect(advance(), TokenType::RIGHT_BRACE);
        expect(advance(), TokenType::SEMICOLON);

        auto stmt = std::make_unique<DeclareStructStatement>();
        stmt->name = std::get<std::string>(name_token.value);
        stmt->methods = std::move(methods);
        // stmt->members = std::move(members);

        return stmt;
    }

    auto Parser::parse_layout_statement() -> StatementPtr {
        expect(advance(), TokenType::LAYOUT);
        expect(advance(), TokenType::LEFT_PAREN);
        expect(advance(), TokenType::LOCATION);
        expect(advance(), TokenType::EQUAL);
        Token location = peek();
        expect(advance(), TokenType::INT_CONSTANT);
        expect(advance(), TokenType::RIGHT_PAREN);
        Token way = advance();
        Token type = advance();
        Token name = expect(advance(), TokenType::IDENTIFIER);
        expect(advance(), TokenType::SEMICOLON);

        auto stmt = std::make_unique<LocationStatement>();

        stmt->location = static_cast<u32>(std::get<i64>(location.value));
        stmt->way = way;
        stmt->type = type;
        stmt->name = std::get<std::string>(name.value);

        return stmt;
    }

    auto Parser::parse_expression() -> ExpressionPtr {
        return parse_bin_op_rhs(0, parse_primary_expression());
    }

    auto Parser::parse_bin_op_rhs(i32 expr_precedence, ExpressionPtr lhs) -> ExpressionPtr {
        // return lhs;
        for (;;) {
            const Token &token = peek();
            TokenType current_token_type = token.type;
            i32 current_token_precedence = get_token_precedence(current_token_type);
            if (current_token_precedence < expr_precedence) {
                return lhs;
            }

            // this only happens when identifier has after parenthesis
            if (TokenType::LEFT_PAREN == current_token_type) {
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
            const Token &next_token = peek();
            i32 next_token_precedence = get_token_precedence(next_token.type);
            if (current_token_precedence < next_token_precedence)
                rhs = parse_bin_op_rhs(current_token_precedence - 1, std::move(rhs));

            lhs = [&] {
                switch (current_token_type) {
                    case TokenType::DOT: return build_identifier_access(std::move(lhs), std::move(rhs));
                    /*case TokenType::LEFT_BRACKET: return build_index_access(std::move(lhs), std::move(rhs));*/
                    case TokenType::STAR: return build_binary(BinaryType::Multiply, std::move(lhs), std::move(rhs));
                    case TokenType::SLASH: return build_binary(BinaryType::Divide, std::move(lhs), std::move(rhs));
                    case TokenType::MODULO: return build_binary(BinaryType::Modulo, std::move(lhs), std::move(rhs));
                    case TokenType::PLUS: return build_binary(BinaryType::Add, std::move(lhs), std::move(rhs));
                    case TokenType::MINUS: return build_binary(BinaryType::Subtract, std::move(lhs), std::move(rhs));
                    /*case TokenType::LEFT_OP: return build_binary(BinaryType::BitShiftLeft, std::move(lhs), std::move(rhs));
                    case TokenType::RIGHT_OP: return build_binary(BinaryType::BitShiftRight, std::move(lhs), std::move(rhs));*/
                    case TokenType::LESS: return build_binary(BinaryType::CompLt, std::move(lhs), std::move(rhs));
                    case TokenType::GREATER: return build_binary(BinaryType::CompGt, std::move(lhs), std::move(rhs));
                    case TokenType::LESS_EQUAL: return build_binary(BinaryType::CompLe, std::move(lhs), std::move(rhs));
                    case TokenType::GREATER_EQUAL: return build_binary(BinaryType::CompGe, std::move(lhs), std::move(rhs));
                    case TokenType::EQUAL_EQUAL: return build_binary(BinaryType::CompEq, std::move(lhs), std::move(rhs));
                    case TokenType::BANG_EQUAL: return build_binary(BinaryType::CompNe, std::move(lhs), std::move(rhs));
                    /*case TokenType::AMPERSAND: return build_binary(BinaryType::BitAnd, std::move(lhs), std::move(rhs));
                    case TokenType::CARET: return build_binary(BinaryType::BitExOr, std::move(lhs), std::move(rhs));
                    case TokenType::VERTICAL_BAR: return build_binary(BinaryType::BitInOr, std::move(lhs), std::move(rhs));*/
                    case TokenType::AND: return build_binary(BinaryType::LogicalAnd, std::move(lhs), std::move(rhs));
                    case TokenType::OR: return build_binary(BinaryType::LogicalOr, std::move(lhs), std::move(rhs));
                    default:
                        throw std::runtime_error("bozo");
                }
            }();
        }
        return {};
    }

    auto Parser::parse_primary_expression() -> ExpressionPtr {
        const Token &token = peek(0);
        ExpressionPtr primary_expr;
        switch (token.type) {
            case TokenType::PLUS: {
                consume();
                ExpressionPtr expr = parse_expression();
                auto plus_expr = std::make_unique<UnaryExpression>();
                plus_expr->type = UnaryType::Plus;
                plus_expr->expr = std::move(expr);
                primary_expr = std::move(plus_expr);
                break;
            }
            case TokenType::MINUS: {
                consume();
                ExpressionPtr expr = parse_expression();
                auto minus_expr = std::make_unique<UnaryExpression>();
                minus_expr->type = UnaryType::Minus;
                minus_expr->expr = std::move(expr);
                primary_expr = std::move(minus_expr);
                break;
            }
            case TokenType::BANG: {
                consume();
                ExpressionPtr expr = parse_expression();
                auto bang_expr = std::make_unique<UnaryExpression>();
                bang_expr->type = UnaryType::LogicalNot;
                bang_expr->expr = std::move(expr);
                primary_expr = std::move(bang_expr);
                break;
            }
            case TokenType::LEFT_PAREN: {
                primary_expr = parse_parenthesis_expression();
                break;
            }
            case TokenType::IDENTIFIER: {
                primary_expr = parse_constant_expression();
                break;
            }
            default: {
                if (is_constant(token.type)) {
                    primary_expr = parse_constant_expression();
                    break;
                } else if (is_type(token.type)) {
                    primary_expr = parse_constructor_expression();
                    break;
                } else {
                    token.print();
                    throw std::runtime_error("unhandled primary expression");
                }
            }
        }

        return primary_expr;
    }

    auto Parser::parse_constant_expression() -> ExpressionPtr {
        auto expr = std::make_unique<ConstantValueExpression>();
        expr->token = advance();
        return expr;
    }

    auto Parser::parse_parenthesis_expression() -> ExpressionPtr {
        expect(advance(), TokenType::LEFT_PAREN);
        ExpressionPtr expr = parse_expression();
        expect(advance(), TokenType::RIGHT_PAREN);
        return expr;
    }

    auto Parser::parse_expression_list() -> std::vector<ExpressionPtr> {
        std::vector<ExpressionPtr> parameters;
        bool first = true;
        while (peek().type != TokenType::RIGHT_PAREN) {
            if (!first) {
                expect(advance(), TokenType::COMMA);
            }
            first = false;
            parameters.push_back(parse_expression());
        }
        expect(advance(), TokenType::RIGHT_PAREN);

        return parameters;
    }

    auto Parser::parse_constructor_expression() -> ExpressionPtr {
        auto constructor_expr = std::make_unique<ConstructorExpression>();
        // INFO("{}", Lexer::token_to_string_view(peek()));
        constructor_expr->type = advance();
        expect(advance(), TokenType::LEFT_PAREN);
        constructor_expr->values = parse_expression_list();
        return constructor_expr;
    }

    auto Parser::get_token_precedence(const TokenType &token) -> i32 {
        switch (token) {
            case TokenType::DOT: return 150;
            case TokenType::LEFT_PAREN: return 100;
            case TokenType::STAR: return 80;
            case TokenType::SLASH: return 80;
            case TokenType::MODULO: return 80;
            case TokenType::PLUS: return 60;
            case TokenType::MINUS: return 60;
            /*case TokenType::LEFT_OP: return 30;
            case TokenType::RIGHT_OP: return 30;*/
            case TokenType::LESS: return 40;
            case TokenType::GREATER: return 40;
            case TokenType::LESS_EQUAL: return 40;
            case TokenType::GREATER_EQUAL: return 40;
            case TokenType::EQUAL_EQUAL: return 50;
            case TokenType::BANG_EQUAL: return 50;
            /*case TokenType::AMPERSAND: return 30;
            case TokenType::CARET: return 30;
            case TokenType::VERTICAL_BAR: return 30;*/
            case TokenType::AND: return 30;
            case TokenType::OR: return 30;
            default: return -1;
        }
        return -1;
    }

    auto Parser::build_identifier_access(ExpressionPtr lhs, ExpressionPtr rhs) -> ExpressionPtr {
        if (ExpressionType::ConstantValueExpression == rhs->get_type()) {
            auto expr = std::make_unique<AccessIdentifierExpression>();
            expr->expr = std::move(lhs);
            expr->identifiers.push_back(std::move(std::get<std::string>(dynamic_cast<ConstantValueExpression *>(rhs.get())->token.value)));
            return expr;
        } else {
            throw std::runtime_error("error cringe" + std::string{lhs->get_name()} + " " + std::string{rhs->get_name()});
        }
    }

    auto Parser::build_binary(BinaryType binary_type, ExpressionPtr lhs, ExpressionPtr rhs) -> ExpressionPtr {
        auto expr = std::make_unique<BinaryExpression>();
        expr->type = binary_type;
        expr->left = std::move(lhs);
        expr->right = std::move(rhs);
        return expr;
    }
} // namespace haflsl