#include <haflsl/nodes.hpp>
#include <haflsl/visitor.hpp>

namespace haflsl {
    void ConstantValueExpression::visit(ExpressionVisitor &visitor) {
        visitor.visit(*this);
    }

    void BinaryExpression::visit(ExpressionVisitor &visitor) {
        visitor.visit(*this);
    }

    void UnaryExpression::visit(ExpressionVisitor &visitor) {
        visitor.visit(*this);
    }

    void IdentifierExpression::visit(ExpressionVisitor &visitor) {
        visitor.visit(*this);
    }

    void AccessIdentifierExpression::visit(ExpressionVisitor &visitor) {
        visitor.visit(*this);
    }

    void AccessIndexExpression::visit(ExpressionVisitor &visitor) {
        visitor.visit(*this);
    }

    void AssignExpression::visit(ExpressionVisitor &visitor) {
        visitor.visit(*this);
    }

    void CallFunctionExpression::visit(ExpressionVisitor &visitor) {
        visitor.visit(*this);
    }

    void ConstructorExpression::visit(ExpressionVisitor &visitor) {
        visitor.visit(*this);
    }

    void BreakStatement::visit(StatementVisitor &visitor) {
        visitor.visit(*this);
    }

    void ContinueStatement::visit(StatementVisitor &visitor) {
        visitor.visit(*this);
    }

    void DiscardStatement::visit(StatementVisitor &visitor) {
        visitor.visit(*this);
    }

    void ReturnStatement::visit(StatementVisitor &visitor) {
        visitor.visit(*this);
    }

    void DeclareFunctionStatement::visit(StatementVisitor &visitor) {
        visitor.visit(*this);
    }

    void DeclareStructStatement::visit(StatementVisitor &visitor) {
        visitor.visit(*this);
    }

    void DeclareVariableStatement::visit(StatementVisitor &visitor) {
        visitor.visit(*this);
    }

    void MultiStatement::visit(StatementVisitor &visitor) {
        visitor.visit(*this);
    }

    void ScopedStatement::visit(StatementVisitor &visitor) {
        visitor.visit(*this);
    }

    void BranchStatement::visit(StatementVisitor &visitor) {
        visitor.visit(*this);
    }

    void WhileStatement::visit(StatementVisitor &visitor) {
        visitor.visit(*this);
    }

    void ForStatement::visit(StatementVisitor &visitor) {
        visitor.visit(*this);
    }

    void ExpressionStatement::visit(StatementVisitor &visitor) {
        visitor.visit(*this);
    }

    // void LocationStatement::visit(StatementVisitor &visitor) {
    //     visitor.visit(*this);
    // }

    void PrintStatement::visit(StatementVisitor &visitor) {
        visitor.visit(*this);
    }
} // namespace haflsl
