#include <haflsl/value.hpp>

#include <iostream>
#include <haflsl/chunk.hpp>

namespace haflsl {
    Function::Function(Type _type) : type{_type} {
        chunk = std::make_unique<Chunk>();
    }

    void Function::print() {
        if (name.empty()) {
            printf("<script>");
            return;
        }

        printf("<fn %s>", name.c_str());
    }

    Closure::Closure(const std::shared_ptr<Function> &_function) {
        function = _function;
        upvalues.resize(function->upvalue_count);
    }

    BoundMethod::BoundMethod(const Value &_reciever, const std::shared_ptr<Closure> _method) : reciever{std::make_unique<Value>(_reciever)}, method{_method} {}

    Class::Class(const std::string &_name) : name{_name} {}

    Instance::Instance(const std::shared_ptr<Class> &_klass) : klass{_klass} {}

    void print_value(const Value &value) {
        switch (value.held_type) {
            case Value::Type::BOOL: {
                std::get<bool>(value.value) ? printf("true") : printf("false");
                break;
            }
            case Value::Type::INT: {
                printf("%li", std::get<i64>(value.value));
                break;
            }
            case Value::Type::FLOAT: {
                printf("%f", std::get<f64>(value.value));
                break;
            }
            case Value::Type::STRING: {
                printf("%s", std::get<std::string>(value.value).c_str());
                break;
            }
            case Value::Type::FUNCTION: {
                (std::get<std::shared_ptr<Function>>(value.value))->print();
                break;
            }
            case Value::Type::CLOSURE: {
                (std::get<std::shared_ptr<Closure>>(value.value))->function->print();
                break;
            }
            case Value::Type::CLASS: {
                printf("%s", (std::get<std::shared_ptr<Class>>(value.value))->name.c_str());
                break;
            }
            case Value::Type::INSTANCE:
                printf("%s instance", (std::get<std::shared_ptr<Instance>>(value.value))->klass->name.c_str());
                break;
            case Value::Type::BOUND_METHOD:
                (std::get<std::shared_ptr<BoundMethod>>(value.value))->method->function->print();
                break;
        }
    }
} // namespace haflsl
