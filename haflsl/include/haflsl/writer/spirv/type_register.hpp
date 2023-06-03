#pragma once 

#include "haflsl/token.hpp"
#include <haflsl/visitor.hpp>
#include <haflsl/writer/spirv/code_buffer.hpp>
#include <unordered_map>

namespace haflsl {
    struct SpvType {
        TokenType type = TokenType::EOS;
        bool function = false;

        bool operator==(const SpvType &other) const {
            return type == other.type && function == other.function;
        }
    };

    struct SpvTypeHash {
        auto operator()(const SpvType &p) const -> size_t {
            size_t seed = 0;
            seed ^= std::hash<haflsl::types::u32>()(static_cast<haflsl::types::u32>(p.type));
            seed ^= std::hash<bool>()(p.function);
            return seed;
        }
    };

    using ID = u32;

    struct TypeRegister : public ExpressionVisitor, public StatementVisitor {
        TypeRegister() = default;
        ~TypeRegister() override = default;

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

        auto register_type(TokenType type, bool fn) -> u32;

        std::unordered_map<SpvType, ID, SpvTypeHash> types;

        CodeBuffer spirv;
    };
}