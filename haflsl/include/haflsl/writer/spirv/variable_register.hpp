#pragma once

#include "haflsl/token.hpp"
#include <haflsl/visitor.hpp>
#include <haflsl/writer/spirv/code_buffer.hpp>
#include <haflsl/writer/spirv/type_register.hpp>
#include <unordered_map>

namespace haflsl {
    using Name = std::string;
    using ID = u32;

    struct SpvPointer {
        EStorageClass storage_class = {};
        TokenType type = {};

        bool operator==(const SpvPointer &other) const {
            return storage_class == other.storage_class && type == other.type;
        }
    };

    struct SpvPointerHash {
        auto operator()(const SpvPointer &p) const -> size_t {
            size_t seed = 0;
            seed ^= std::hash<haflsl::types::u32>()(static_cast<haflsl::types::u32>(p.storage_class));
            seed ^= std::hash<haflsl::types::u32>()(static_cast<haflsl::types::u32>(p.type));
            return seed;
        }
    };

    struct SpvVariable {
        SpvPointer spv_pointer;
        u32 id = {};
    };

    struct VariableRegister : public ExpressionVisitor, public StatementVisitor {
        VariableRegister(const std::unordered_map<SpvType, ID, SpvTypeHash> &_types, const std::unordered_map<Name, ID>& _names);
        ~VariableRegister() override = default;

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
        void visit(LocationStatement &node) override;
        void visit(PrintStatement &node) override;

        void register_variable(const std::string &name, EStorageClass storage, SpvType type);
        auto register_pointer(EStorageClass storage, const SpvType& spv_type) -> ID;

        std::unordered_map<SpvPointer, ID, SpvPointerHash> pointers;
        std::unordered_map<Name, SpvVariable> variables;

        std::unordered_map<SpvType, ID, SpvTypeHash> types;
        std::unordered_map<Name, ID> names;

        CodeBuffer spirv;
    };
} // namespace haflsl