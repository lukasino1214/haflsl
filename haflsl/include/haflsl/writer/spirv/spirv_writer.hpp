#pragma once

#include <haflsl/result.hpp>
#include <haflsl/visitor.hpp>
#include <haflsl/writer/spirv/code_buffer.hpp>
#include <haflsl/writer/spirv/name_register.hpp>
#include <haflsl/writer/spirv/type_register.hpp>
#include <haflsl/writer/spirv/variable_register.hpp>
#include <haflsl/writer/spirv/constant_register.hpp>

namespace haflsl {
    using SPIRV = std::vector<u32>;

    struct SpirvWriter : public ExpressionVisitor, public StatementVisitor {
        SpirvWriter();
        ~SpirvWriter() override;

        auto compile(const std::vector<StatementPtr> &ast) -> Result<SPIRV>;

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

        std::unique_ptr<CodeBuffer> spirv;
        std::unordered_map<Name, ID> names;
        std::unordered_map<SpvType, ID, SpvTypeHash> types;
        std::unordered_map<SpvPointer, ID, SpvPointerHash> pointers;
        std::unordered_map<Name, SpvVariable> variables;
        std::unordered_map<SpvConstant, ID, SpvConstantHash> constants;

        std::vector<StatementType> stmt_queue = {};
        std::vector<ExpressionType> expr_queue = {};

        ID object_id = {};
        ID constant_id = {};

        std::vector<u32> constructor_values = {};
    };
} // namespace haflsl