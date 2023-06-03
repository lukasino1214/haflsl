#include "haflsl/writer/spirv/code_buffer.hpp"
#include <haflsl/writer/spirv/variable_register.hpp>
#include <stdexcept>

namespace haflsl {
    VariableRegister::VariableRegister(const std::unordered_map<SpvType, ID, SpvTypeHash>& _types, const std::unordered_map<Name, ID>& _names) : types{_types}, names{_names} {}

    void VariableRegister::visit(ConstantValueExpression &node) {

    }

    void VariableRegister::visit(BinaryExpression &node) {

    }

    void VariableRegister::visit(UnaryExpression &node) {

    }

    void VariableRegister::visit(IdentifierExpression &node) {

    }

    void VariableRegister::visit(AccessIdentifierExpression &node) {

    }

    void VariableRegister::visit(AccessIndexExpression &node) {

    }

    void VariableRegister::visit(AssignExpression &node) {

    }

    void VariableRegister::visit(CallFunctionExpression &node) {

    }

    void VariableRegister::visit(ConstructorExpression &node) {

    }

    void VariableRegister::visit(BreakStatement &node) {

    }

    void VariableRegister::visit(ContinueStatement &node) {

    }

    void VariableRegister::visit(DiscardStatement &node) {

    }

    void VariableRegister::visit(ReturnStatement &node) {

    }

    void VariableRegister::visit(DeclareFunctionStatement &node) {

    }

    void VariableRegister::visit(DeclareStructStatement &node) {

    }

    void VariableRegister::visit(DeclareVariableStatement &node) {

    }

    void VariableRegister::visit(MultiStatement &node) {

    }

    void VariableRegister::visit(ScopedStatement &node) {

    }

    void VariableRegister::visit(BranchStatement &node) {

    }

    void VariableRegister::visit(WhileStatement &node) {

    }

    void VariableRegister::visit(ForStatement &node) {

    }

    void VariableRegister::visit(ExpressionStatement &node) {

    }

    void VariableRegister::visit(LocationStatement &node) {
        register_variable(node.name, EStorageClass::Output, {.type = node.type.type, .function = false });
    }

    void VariableRegister::visit(PrintStatement &node) {

    }

    void VariableRegister::register_variable(const std::string &name, EStorageClass storage, SpvType type) {
        if(variables.find(name) == variables.end()) {
            ID pointer_id = register_pointer(storage, type);

            ID id = 0;
            if(names.find(name) != names.end()) {
                id = names.at(name);
            }

            //ID id = spirv.register_new_id();
            spirv.OpVariable(pointer_id, id, storage, 0);
            variables.insert({name, SpvVariable { .spv_pointer = SpvPointer { .storage_class = storage, .type = type.type }, .id = id }});
        } else {
            throw std::runtime_error("variable name was already registered");
        }
    }

    auto VariableRegister::register_pointer(EStorageClass storage, const SpvType& spv_type) -> ID {
        if(pointers.find(SpvPointer {.storage_class = storage, .type = spv_type.type}) == pointers.end()) {
            // idk if function should be false or true
            ID type_id = 0;
            if(types.find(spv_type) != types.end()) {
                type_id = types.at(spv_type);
            } else {
                throw std::runtime_error("register variable couldnt find name");
            }

            ID id = spirv.register_new_id();
            spirv.OpTypePointer(id, storage, type_id);
            pointers.insert({SpvPointer {.storage_class = storage, .type = spv_type.type}, id});

            return id;
        }

        return pointers.at(SpvPointer {.storage_class = storage, .type = spv_type.type});
    }
}