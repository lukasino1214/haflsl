#include "haflsl/nodes.hpp"
#include <haflsl/writer/bytecode/bytecode_writer.hpp>

#include <iostream>
#include <stdexcept>

namespace haflsl {
    Compiler::Compiler(Function::Type type) {
        function = std::make_shared<Function>(type);
    }

    BytecodeWriter::BytecodeWriter() {}

    BytecodeWriter::~BytecodeWriter() {}

    auto BytecodeWriter::compile(const std::vector<StatementPtr> &ast) -> Result<std::shared_ptr<Function>> {
        current = init_compiler(Function::Type::SCRIPT);

        for (const auto &stmt : ast) {
            stmt->visit(*this);
        }

        current_chunk()->write(OP::EOS, 123);

        return Result<std::shared_ptr<Function>>(current->function);
    }

    void BytecodeWriter::visit(ConstantValueExpression &node) {
        OP get_op = {};
        OP set_op = {};

        i32 arg = -1;
        if (node.token.type == TokenType::IDENTIFIER) {
            arg = resolve_local(current, std::get<std::string>(node.token.value));
            if (arg != -1) {
                get_op = OP::GET_LOCAL;
                set_op = OP::SET_LOCAL;
            } else if ((arg = resolve_Upvalue(current, std::get<std::string>(node.token.value))) != -1) {
                get_op = OP::GET_UPVALUE;
                set_op = OP::SET_UPVALUE;
            } else {
                arg = current_chunk()->add_constant(node.token);
                get_op = OP::GET_GLOBAL;
                set_op = OP::SET_GLOBAL;
            }
        }

        if (node.token.type != TokenType::IDENTIFIER) {
            u32 constant = current_chunk()->add_constant(node.token);

            current_chunk()->write(OP::CONSTANT, 123);
            current_chunk()->write(constant, 123);
        } else if (can_assign && !property) {
            current_chunk()->write(set_op, 123);
            current_chunk()->write(static_cast<u32>(arg), 123);
        } else {
            current_chunk()->write(get_op, 123);
            current_chunk()->write(static_cast<u32>(arg), 123);
        }
    }

    void BytecodeWriter::visit(BinaryExpression &node) {
        node.left->visit(*this);
        node.right->visit(*this);
        switch (node.type) {
            case BinaryType::Multiply: {
                current_chunk()->write(OP::MULTIPLY, 123);
                break;
            }
            case BinaryType::Divide: {
                current_chunk()->write(OP::DIVIDE, 123);
                break;
            }
            case BinaryType::Add: {
                current_chunk()->write(OP::ADD, 123);
                break;
            }
            case BinaryType::Subtract: {
                current_chunk()->write(OP::SUBTRACT, 123);
                break;
            }
            case BinaryType::CompLt: {
                current_chunk()->write(OP::LESS, 123);
                break;
            }
            case BinaryType::CompGt: {
                current_chunk()->write(OP::GREATER, 123);
                break;
            }
            case BinaryType::CompLe: {
                current_chunk()->write(OP::LESS, 123);
                current_chunk()->write(OP::NOT, 123);
                break;
            }
            case BinaryType::CompGe: {
                current_chunk()->write(OP::GREATER, 123);
                current_chunk()->write(OP::NOT, 123);
                break;
            }
            case BinaryType::CompEq: {
                current_chunk()->write(OP::EQUAL, 123);
                break;
            }
            case BinaryType::CompNe: {
                current_chunk()->write(OP::EQUAL, 123);
                current_chunk()->write(OP::NOT, 123);
                break;
            }
            case BinaryType::LogicalAnd: {
                i32 end_jump = emit_jump(OP::JUMP_IF_FALSE);
                current_chunk()->write(OP::POP, 123);
                patch_jump(end_jump);
                break;
            }
            case BinaryType::LogicalOr: {
                i32 else_jump = emit_jump(OP::JUMP_IF_FALSE);
                i32 end_jump = emit_jump(OP::JUMP);
                patch_jump(else_jump);
                current_chunk()->write(OP::POP, 123);
                // parsePrecedence(PREC_OR);
                patch_jump(end_jump);
                break;
            }
            default: throw std::runtime_error("unhandled binary type operation");
        }
    }

    void BytecodeWriter::visit(UnaryExpression &node) {
        node.expr->visit(*this);
        switch (node.type) {
            case UnaryType::LogicalNot: {
                current_chunk()->write(OP::NOT, 123);
                break;
            }
            case UnaryType::Minus: {
                current_chunk()->write(OP::NEGATE, 123);
                break;
            }
            case UnaryType::Plus: {
                break;
            }
            default: throw std::runtime_error("unhandled unary type operation");
        }
    }

    void BytecodeWriter::visit(IdentifierExpression &node) {
    }

    void BytecodeWriter::visit(AccessIdentifierExpression &node) {

        u32 name_constant = current_chunk()->add_constant({.type = TokenType::STRING_CONSTANT, .value = node.identifiers[0]});
        property = true;
        if (can_assign && node.expr) {
            node.expr->visit(*this);
            current_chunk()->write(OP::SET_PROPERTY, 123);
            current_chunk()->write(name_constant, 123);
        } else {
            node.expr->visit(*this);
            current_chunk()->write(OP::GET_PROPERTY, 123);
            current_chunk()->write(name_constant, 123);
        }
        property = false;
    }

    void BytecodeWriter::visit(AccessIndexExpression &node) {
    }

    void BytecodeWriter::visit(AssignExpression &node) {
        auto &right = node.right;
        auto &left = node.left;

        switch (node.type) {
            case AssignType::Simple: {
                right->visit(*this);

                can_assign = true;
                left->visit(*this);
                can_assign = false;
                break;
            }
            case AssignType::CompoundAdd: {
                right->visit(*this);
                // gets the variable value to stack
                left->visit(*this);
                current_chunk()->write(OP::ADD, 123);

                // assigns it
                can_assign = true;
                left->visit(*this);
                can_assign = false;

                break;
            }
            case AssignType::CompoundSubtract: {
                left->visit(*this);
                right->visit(*this);
                current_chunk()->write(OP::SUBTRACT, 123);

                can_assign = true;
                left->visit(*this);
                can_assign = false;

                break;
            }
            case AssignType::CompoundMultiply: {
                left->visit(*this);
                right->visit(*this);
                current_chunk()->write(OP::MULTIPLY, 123);

                can_assign = true;
                left->visit(*this);
                can_assign = false;

                break;
            }
            case AssignType::CompoundDivide: {
                left->visit(*this);
                right->visit(*this);
                current_chunk()->write(OP::DIVIDE, 123);

                can_assign = true;
                left->visit(*this);
                can_assign = false;

                break;
            }
            default: {
                throw std::runtime_error("unhandled assign type");
            }
        }
    }

    void BytecodeWriter::visit(CallFunctionExpression &node) {
        node.function_expr->visit(*this);

        for (auto &par : node.parameters) {
            par->visit(*this);
        }
        u32 arg_count = node.parameters.size();
        current_chunk()->write(OP::CALL, 123);
        current_chunk()->write(arg_count, 123);
    }

    void BytecodeWriter::visit(ConstructorExpression &node) {
    }

    void BytecodeWriter::visit(BreakStatement &node) {
    }

    void BytecodeWriter::visit(ContinueStatement &node) {
    }

    void BytecodeWriter::visit(DiscardStatement &node) {
    }

    void BytecodeWriter::visit(ReturnStatement &node) {
        if (current->function->type == Function::Type::SCRIPT) {
            throw std::runtime_error("cannot return from script");
        }

        node.expr->visit(*this);
        current_chunk()->write(OP::RETURN, 123);
    }

    void BytecodeWriter::visit(DeclareFunctionStatement &node) {
        /*for (auto &stmt : node.statements) {
            stmt->visit(*this);
        }*/
        if (!method) {
            u32 global = parseVariable(node.name);
            markInitialized();

            auto compiler = init_compiler(Function::Type::FUNCTION);
            compiler->function->name = node.name;
            compiler->function->arity = node.parameters.size();
            current = std::move(compiler);

            begin_scope();
            for (auto &par : node.parameters) {
                u32 param_constant = parseVariable(par.name);
                defineVariable(param_constant);
            }

            for (auto &stmt : node.statements) {
                stmt->visit(*this);
            }

            auto function = end_compiler();
            // function->chunk->disassemble("FINALLY");
            current_chunk()->write(OP::CLOSURE, 123);
            u32 constant = current_chunk()->add_constant(std::make_shared<Closure>(function));
            current_chunk()->write(constant, 123);
            for (int i = 0; i < function->upvalue_count; i++) {
                current_chunk()->write(current->upvalues[i].is_local ? 1 : 0, 123);
                current_chunk()->write(current->upvalues[i].index, 123);
            }

            defineVariable(global);
        } else {
            if (node.name == "init") {
                initializer = true;
            }

            // uint8_t constant = identifierConstant(&parser.previous);
            u32 name_constant = current_chunk()->add_constant({.type = TokenType::STRING_CONSTANT, .value = node.name});

            auto compiler = init_compiler(Function::Type::METHOD);
            compiler->function->name = node.name;
            compiler->function->arity = node.parameters.size();
            current = std::move(compiler);

            begin_scope();
            for (auto &par : node.parameters) {
                u32 param_constant = parseVariable(par.name);
                defineVariable(param_constant);
            }

            for (auto &stmt : node.statements) {
                stmt->visit(*this);
            }

            auto function = end_compiler();
            // function->chunk->disassemble("FINALLY");
            current_chunk()->write(OP::CLOSURE, 123);
            u32 constant = current_chunk()->add_constant(std::make_shared<Closure>(function));
            current_chunk()->write(constant, 123);
            for (int i = 0; i < function->upvalue_count; i++) {
                current_chunk()->write(current->upvalues[i].is_local ? 1 : 0, 123);
                current_chunk()->write(current->upvalues[i].index, 123);
            }

            current_chunk()->write(OP::METHOD, 123);
            current_chunk()->write(name_constant, 123);
            initializer = false;
        }
    }

    void BytecodeWriter::visit(DeclareStructStatement &node) {
        // u32 nameConstant = identifierConstant(&parser.previous);
        u32 name_constant = current_chunk()->add_constant({.type = TokenType::STRING_CONSTANT, .value = node.name});
        declareVariable(node.name);
        current_chunk()->write(OP::CLASS, 123);
        current_chunk()->write(name_constant, 123);
        defineVariable(name_constant);

        {
            OP get_op = {};
            OP set_op = {};

            i32 arg = -1;
            arg = resolve_local(current, node.name);
            if (arg != -1) {
                get_op = OP::GET_LOCAL;
                set_op = OP::SET_LOCAL;
            } else if ((arg = resolve_Upvalue(current, node.name)) != -1) {
                get_op = OP::GET_UPVALUE;
                set_op = OP::SET_UPVALUE;
            } else {
                arg = current_chunk()->add_constant({.type = TokenType::STRING_CONSTANT, .value = node.name});
                get_op = OP::GET_GLOBAL;
                set_op = OP::SET_GLOBAL;
            }

            if (false) {
                u32 constant = current_chunk()->add_constant({.type = TokenType::STRING_CONSTANT, .value = node.name});

                current_chunk()->write(OP::CONSTANT, 123);
                current_chunk()->write(constant, 123);
            } else if (false && !property) {
                current_chunk()->write(set_op, 123);
                current_chunk()->write(static_cast<u32>(arg), 123);
            } else {
                current_chunk()->write(get_op, 123);
                current_chunk()->write(static_cast<u32>(arg), 123);
            }
        }

        method = true;
        for (auto &m : node.methods) {
            m->visit(*this);
        }
        current_chunk()->write(OP::POP, 123);
        method = false;
    }

    void BytecodeWriter::visit(DeclareVariableStatement &node) {
        u32 global = parseVariable(node.name);

        node.expression->visit(*this);
        defineVariable(global);
    }

    void BytecodeWriter::visit(MultiStatement &node) {
        for (auto &stmt : node.statements) {
            stmt->visit(*this);
        }
    }

    void BytecodeWriter::visit(ScopedStatement &node) {
        begin_scope();
        node.statement->visit(*this);
        end_scope();
    };

    void BytecodeWriter::visit(BranchStatement &node) {
        if (node.conditional_statements.size() > 1) {
            throw std::runtime_error("mroe than 1 conditinal statmenets");
        }

        node.conditional_statements[0].condition->visit(*this);
        i32 then_jump = emit_jump(OP::JUMP_IF_FALSE);
        current_chunk()->write(OP::POP, 123);
        node.conditional_statements[0].statement->visit(*this);
        i32 else_jump = emit_jump(OP::JUMP);
        patch_jump(then_jump);
        current_chunk()->write(OP::POP, 123);
        if (node.else_statement) {
            node.else_statement->visit(*this);
        }
        patch_jump(else_jump);
    }

    void BytecodeWriter::visit(WhileStatement &node) {
        i32 loop_start = current_chunk()->code.size();
        node.condition->visit(*this);

        i32 exit_jump = emit_jump(OP::JUMP_IF_FALSE);
        current_chunk()->write(OP::POP, 123);

        node.statement->visit(*this);
        emit_loop(loop_start);
        patch_jump(exit_jump);
        current_chunk()->write(OP::POP, 123);
    }

    void BytecodeWriter::visit(ForStatement &node) {
        begin_scope();

        if (node.iterable) {
            node.iterable->visit(*this);
        }

        i32 loop_start = current_chunk()->code.size();
        i32 exit_jump = -1;

        if (node.condition) {
            node.condition->visit(*this);
            exit_jump = emit_jump(OP::JUMP_IF_FALSE);
            current_chunk()->write(OP::POP, 123);
        }

        if (node.step) {
            i32 body_jump = emit_jump(OP::JUMP);
            i32 increment_start = current_chunk()->code.size();
            node.step->visit(*this);
            current_chunk()->write(OP::POP, 123);
            emit_loop(loop_start);
            loop_start = increment_start;
            patch_jump(body_jump);
        }

        node.statement->visit(*this);
        emit_loop(loop_start);

        if (exit_jump != -1) {
            patch_jump(exit_jump);
            current_chunk()->write(OP::POP, 123);
        }

        end_scope();
    }

    void BytecodeWriter::visit(ExpressionStatement &node) {
        node.expression->visit(*this);
        current_chunk()->write(OP::POP, 123);
    }

    void BytecodeWriter::visit(LocationStatement &node) {
        throw std::runtime_error("cant use location statement in scripting");
    }

    void BytecodeWriter::visit(PrintStatement &node) {
        node.expression->visit(*this);
        current_chunk()->write(OP::PRINT, 123);
    }

    void BytecodeWriter::begin_scope() {
        current->scope_depth++;
    }

    void BytecodeWriter::end_scope() {
        current->scope_depth--;

        while (current->locals.size() > 0 && current->locals[current->locals.size() - 1].depth > current->scope_depth) {
            if (current->locals[current->locals.size() - 1].is_captured) {
                current_chunk()->write(OP::CLOSE_UPVALUE, 123);
            } else {
                current_chunk()->write(OP::POP, 123);
            }
            current->locals.pop_back();
        }
    }

    void BytecodeWriter::add_local(const std::string &name) {
        current->locals.push_back(Local{.name = name, .depth = -1});
    }

    auto BytecodeWriter::resolve_local(const std::unique_ptr<Compiler> &compiler, const std::string &name) -> i32 {
        for (int i = compiler->locals.size() - 1; i >= 0; i--) {
            Local *local = &compiler->locals[i];
            if (name == local->name) {
                return i;
            }
        }
        return -1;
    }

    auto BytecodeWriter::emit_jump(OP instruction) -> i32 {
        current_chunk()->write(instruction, 123);
        current_chunk()->write(0xff, 123);
        current_chunk()->write(0xff, 123);
        return current_chunk()->code.size() - 2;
    }

    void BytecodeWriter::patch_jump(i32 offset) {
        int jump = current_chunk()->code.size() - offset - 2;

        current_chunk()->code[offset] = (jump >> 8) & 0xff;
        current_chunk()->code[offset + 1] = jump & 0xff;
    }

    void BytecodeWriter::emit_loop(i32 loop_start) {
        current_chunk()->write(OP::LOOP, 123);
        int offset = current_chunk()->code.size() - loop_start + 2;
        current_chunk()->write((offset >> 8) & 0xff, 123);
        current_chunk()->write(offset & 0xff, 123);
    }

    void BytecodeWriter::declareVariable(const std::string &name) {
        if (current->scope_depth == 0)
            return;
        for (int i = current->locals.size() - 1; i >= 0; i--) {
            Local *local = &current->locals[i];
            if (local->depth != -1 && local->depth < current->scope_depth) {
                break;
            }
            if (name == local->name) {
                throw std::runtime_error("Already variable with this name in this scope.");
            }
        }
        add_local(name);
    }

    u32 BytecodeWriter::parseVariable(const std::string &name) {
        declareVariable(name);
        if (current->scope_depth > 0)
            return 0;

        u32 constant = current_chunk()->add_constant({.type = TokenType::STRING_CONSTANT, .value = name});
        return constant;
    }

    void BytecodeWriter::markInitialized() {
        if (current->scope_depth == 0)
            return;
        current->locals[current->locals.size() - 1].depth = current->scope_depth;
    }

    void BytecodeWriter::defineVariable(u32 global) {
        if (current->scope_depth > 0) {
            markInitialized();
            return;
        }

        current_chunk()->write(OP::DEFINE_GLOBAL, 123);
        current_chunk()->write(global, 123);
    }

    auto BytecodeWriter::current_chunk() -> std::unique_ptr<Chunk> & {
        return current->function->chunk;
    }

    auto BytecodeWriter::init_compiler(Function::Type type) -> std::unique_ptr<Compiler> {
        auto compiler = std::make_unique<Compiler>(type);
        compiler->enclosing = std::move(current);
        if (type == Function::Type::SCRIPT) {
            compiler->locals.push_back({.name = "", .depth = 0});
        } else {
            compiler->locals.push_back({.name = "this", .depth = 0});
        }
        return compiler;
    }

    auto BytecodeWriter::end_compiler() -> std::shared_ptr<Function> {
        if (initializer) {
            current_chunk()->write(OP::GET_LOCAL, 123);
            current_chunk()->write(0, 123);
        } else {
            current_chunk()->write(OP::NIL, 123);
        }
        current_chunk()->write(OP::RETURN, 123);
        auto function = current->function;
        current = std::move(current->enclosing);
        return function;
    }

    auto BytecodeWriter::resolve_Upvalue(const std::unique_ptr<Compiler> &compiler, const std::string &name) -> i32 {
        if (compiler->enclosing == nullptr) {
            return -1;
        }
        int local = resolve_local(compiler->enclosing, name);
        if (local != -1) {
            compiler->enclosing->locals[local].is_captured = true;
            return add_Upvalue(local, true);
        }

        int upvalue = resolve_Upvalue(compiler->enclosing, name);
        if (upvalue != -1) {
            return add_Upvalue(upvalue, false);
        }

        return -1;
    }

    auto BytecodeWriter::add_Upvalue(u32 index, bool is_local) -> i32 {
        u32 upvalue_count = current->function->upvalue_count;

        for (int i = 0; i < upvalue_count; i++) {
            Upvalue *upvalue = &current->upvalues[i];
            if (upvalue->index == index && upvalue->is_local == is_local) {
                return i;
            }
        }

        current->upvalues[upvalue_count].is_local = is_local;
        current->upvalues[upvalue_count].index = index;
        return current->function->upvalue_count++;
    }
} // namespace haflsl