#pragma once

#include "haflsl/token.hpp"
#include <haflsl/visitor.hpp>
#include <haflsl/writer/spirv/code_buffer.hpp>
#include <haflsl/writer/spirv/type_register.hpp>
#include <unordered_map>

namespace haflsl {
    struct SpvConstant {
        TokenType type;
        std::vector<u32> values;

        bool operator==(const SpvConstant &other) const {
            bool same = true;
            if(values.size() == other.values.size()) {
                for(u32 i = 0; i < values.size(); i++) {
                    if(values[i] != other.values[i]) { same = false; }
                }
            } else { same = false; }

            return type == other.type && same;
        }
    };

    struct SpvConstantHash {
        auto operator()(const SpvConstant &p) const -> size_t {
            size_t seed = 0;
            seed ^= std::hash<haflsl::types::u32>()(static_cast<haflsl::types::u32>(p.type));

            for(u32 v : p.values) {
                seed ^= std::hash<haflsl::types::u32>()(v);
            }

            return seed;
        }
    };

    using ID = u32;

    struct ConstantRegister : public ExpressionVisitor, public StatementVisitor {
        ConstantRegister(const std::unordered_map<SpvType, ID, SpvTypeHash>& _types);
        ~ConstantRegister() override = default;

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

        auto register_constant(TokenType type, const std::vector<u32>& values) -> u32;

        bool constructor = false;
        std::vector<ID> constructor_values = {};

        std::unordered_map<SpvConstant, ID, SpvConstantHash> constants;

        std::unordered_map<SpvType, ID, SpvTypeHash> types;

        CodeBuffer spirv;
    };
}