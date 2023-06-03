#pragma once

#include <haflsl/result.hpp>
#include <haflsl/visitor.hpp>
#include <haflsl/chunk.hpp>

namespace haflsl {
    struct Local {
        std::string name = {};
        i32 depth = 0;
        bool is_captured = false;
    };

    struct Upvalue {
        u32 index;
        bool is_local;
    };

    struct Compiler;
    struct Compiler {
        std::unique_ptr<Compiler> enclosing;
        std::shared_ptr<Function> function;
        std::vector<Local> locals = {};
        std::array<Upvalue, 255> upvalues;
        i32 scope_depth = 0;

        Compiler(Function::Type type);
    };

    struct BytecodeWriter : public ExpressionVisitor, public StatementVisitor {
        BytecodeWriter();
        ~BytecodeWriter() override;

        auto compile(const std::vector<StatementPtr> &ast) -> Result<std::shared_ptr<Function>>;

        void visit(ConstantValueExpression &node) override;
        void visit(BinaryExpression &node) override;
        void visit(UnaryExpression &node) override;
        void visit(IdentifierExpression &node) override;
        void visit(AccessIdentifierExpression &node) override;
        void visit(AccessIndexExpression &node) override;
        void visit(AssignExpression &node) override;
        void visit(CallFunctionExpression &node) override;
        void visit(ConstructorExpression &node) override;

        void visit(BreakStatement &node) override;
        void visit(ContinueStatement &node) override;
        void visit(DiscardStatement &node) override;
        void visit(ReturnStatement &node) override;
        void visit(DeclareFunctionStatement &node) override;
        void visit(DeclareStructStatement &node) override;
        void visit(DeclareVariableStatement &node) override;
        void visit(MultiStatement &node) override;
        void visit(ScopedStatement &node) override;
        void visit(BranchStatement &node) override;
        void visit(WhileStatement &node) override;
        void visit(ForStatement &node) override;
        void visit(ExpressionStatement &node) override;
        void visit(LocationStatement& node) override;
        void visit(PrintStatement &node) override;

        void begin_scope();
        void end_scope();

        void add_local(const std::string &name);
        auto resolve_local(const std::unique_ptr<Compiler> &compiler, const std::string &name) -> i32;

        auto emit_jump(OP instruction) -> i32;
        void patch_jump(i32 offset);
        void emit_loop(i32 loop_start);

        u32 parseVariable(const std::string &name);
        void defineVariable(u32 global);
        void markInitialized();
        void declareVariable(const std::string &name);

        auto current_chunk() -> std::unique_ptr<Chunk> &;

        auto init_compiler(Function::Type type) -> std::unique_ptr<Compiler>;
        auto end_compiler() -> std::shared_ptr<Function>;

        auto resolve_Upvalue(const std::unique_ptr<Compiler> &compiler, const std::string &name) -> i32;
        auto add_Upvalue(u32 index, bool is_local) -> i32;

        bool can_assign = false;
        bool property = false;
        bool method = false;
        bool initializer = false;
        std::unique_ptr<Compiler> current;
    };
} // namespace haflsl