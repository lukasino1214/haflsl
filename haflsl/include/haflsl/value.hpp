#pragma once

#include <haflsl/types.hpp>
#include <variant>
#include <string>
#include <memory>
#include <functional>

namespace haflsl {
    struct Value;
    using NativeFn = std::function<Value(u32 arg_count, Value *args)>;

    struct Chunk;
    struct Function {
        enum struct Type : u32 {
            FUNCTION,
            INITIALIZER,
            METHOD,
            SCRIPT
        };

        Type type;
        u32 arity = 0;
        u32 upvalue_count = 0;
        std::unique_ptr<Chunk> chunk;
        std::string name;

        Function(Type _type);

        void print();
    };

    struct Upvalue_;
    struct Closure {
        std::shared_ptr<Function> function;
        std::vector<std::unique_ptr<Upvalue_>> upvalues;

        Closure(const std::shared_ptr<Function> &_function);
    };

    struct Class {
        std::string name;
        std::unordered_map<std::string, Value> methods;

        Class(const std::string &_name);
    };

    struct Instance {
        std::shared_ptr<Class> klass;
        std::unordered_map<std::string, Value> fields;
        Instance(const std::shared_ptr<Class> &_klass);
    };

    struct BoundMethod {
        std::unique_ptr<Value> reciever;
        std::shared_ptr<Closure> method;

        BoundMethod(const Value &_reciever, const std::shared_ptr<Closure> _method);
    };

    struct Value {
        enum struct Type : u32 {
            BOOL,
            INT,
            FLOAT,
            STRING,
            FUNCTION,
            NATIVE,
            CLOSURE,
            CLASS,
            INSTANCE,
            BOUND_METHOD
        };

        std::variant<std::monostate, bool, i64, f64, std::string, std::shared_ptr<Function>, NativeFn, std::shared_ptr<Closure>, std::shared_ptr<Class>, std::shared_ptr<Instance>, std::shared_ptr<BoundMethod>> value = std::monostate{};
        Type held_type;
    };

    struct Upvalue_ {
        Value *location;
        Value closed;
        std::unique_ptr<Upvalue_> next = nullptr;
    };

    void print_value(const Value &value);
} // namespace haflsl