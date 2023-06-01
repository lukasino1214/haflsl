#pragma once

#include <array>
#include <unordered_map>

#define FRAMES_MAX 64
#define STACK_MAX (FRAMES_MAX * 256)

#include <haflsl/chunk.hpp>

namespace haflsl {
    struct CallFrame {
        std::shared_ptr<Closure> closure;
        u32 *ip;
        Value *slots;
    };

    struct VM {
        enum struct InterpretResult : u32 {
            OK,
            COMPILE_ERROR,
            RUNTIME_ERROR
        };

        VM() = default;
        ~VM() = default;

        auto interpret(const std::shared_ptr<Function> &script) -> InterpretResult;

        std::vector<CallFrame> frames;
        std::array<Value, STACK_MAX> stack;
        Value *stack_top = stack.data();
        std::unordered_map<std::string, Value> globals;
        std::unique_ptr<Upvalue_> openUpvalues = nullptr;

      private:
        void reset_stack();

        void push(Value value);
        auto pop() -> Value;
        auto peek(i32 distance) -> Value;
        bool call_value(const Value &callee, i32 arg_count);
        bool call(std::shared_ptr<Closure> closure, i32 arg_count);

        void define_native(const std::string &name, const NativeFn &function);
        auto capture_Upvalue(Value *local) -> std::unique_ptr<Upvalue_>;
        void closeUpvalues(Value *last);

        void defineMethod(const std::string &name);
        bool bindMethod(const std::shared_ptr<Class> &klass, const std::string &name);

        auto run() -> InterpretResult;
    };
} // namespace haflsl