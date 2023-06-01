#include <haflsl/vm.hpp>

#include <iostream>
#include <time.h>
// #define DEBUG_TRACE_EXECUTION

namespace haflsl {
    void VM::reset_stack() {
        stack_top = stack.data();
    }

    void VM::push(Value value) {
        *stack_top = value;
        stack_top++;
    }

    auto VM::pop() -> Value {
        stack_top--;
        return *stack_top;
    }

    auto VM::peek(i32 distance) -> Value {
        return stack_top[-1 - distance];
    }

    auto VM::run() -> InterpretResult {
        CallFrame *frame = &frames.back();
#define READ_BYTE() (*frame->ip++)
#define READ_SHORT() \
    (frame->ip += 2, \
     static_cast<u16>((frame->ip[-2] << 8) | frame->ip[-1]))
#define READ_CONSTANT() \
    (frame->closure->function->chunk->constants[READ_BYTE()])

#define BINARY_OP(op)                                                                                                                            \
    do {                                                                                                                                         \
        Value b = pop();                                                                                                                         \
        Value a = pop();                                                                                                                         \
        if (a.held_type == b.held_type && a.held_type == Value::Type::BOOL) {                                                                    \
            throw std::runtime_error("cant do op with bools");                                                                                   \
        } else if (a.held_type == b.held_type && a.held_type == Value::Type::INT) {                                                              \
            push({.value = std::get<i64>(a.value) op std::get<i64>(b.value), .held_type = Value::Type::INT});                                    \
        } else if (a.held_type == b.held_type && a.held_type == Value::Type::FLOAT) {                                                            \
            push({.value = std::get<f64>(a.value) op std::get<f64>(b.value), .held_type = Value::Type::FLOAT});                                  \
        } else if (a.held_type == b.held_type && a.held_type == Value::Type::STRING) {                                                           \
            if (std::string{#op} == "+") {                                                                                                       \
                push({.value = std::string{std::get<std::string>(a.value) + std::get<std::string>(b.value)}, .held_type = Value::Type::STRING}); \
            } else {                                                                                                                             \
                throw std::runtime_error("cant do op with strings");                                                                             \
            }                                                                                                                                    \
        }                                                                                                                                        \
        /*push(a op b);*/                                                                                                                        \
    } while (false)

        for (;;) {
            // std::cout << frame_count << std::endl;
#ifdef DEBUG_TRACE_EXECUTION
            printf(" ");
            for (Value *slot = stack.data(); slot < stack_top; slot++) {
                printf("[ ");
                print_value(*slot);
                printf(" ]");
            }
            printf("\n");
            frame->closure->function->chunk->disassemble_instruction(static_cast<u32>(frame->ip - frame->closure->function->chunk->code.data()));
#endif

            OP instruction;
            switch (instruction = static_cast<OP>(READ_BYTE())) {
                case OP::CONSTANT: {
                    Value constant = READ_CONSTANT();
                    push(constant);
                    // print_value(constant);
                    // printf("\n");
                    break;
                }
                case OP::DEFINE_GLOBAL: {
                    std::string name = std::get<std::string>(READ_CONSTANT().value);
                    globals.insert({name, peek(0)});
                    pop();
                    break;
                }
                case OP::GET_GLOBAL: {
                    std::string name = std::get<std::string>(READ_CONSTANT().value);
                    Value value;
                    if (globals.find(name) == globals.end()) {
                        throw std::runtime_error("undefined variable: " + name);
                    }

                    value = globals.at(name);
                    push(value);
                    break;
                }
                case OP::SET_GLOBAL: {
                    std::string name = std::get<std::string>(READ_CONSTANT().value);
                    if (globals.find(name) == globals.end()) {
                        throw std::runtime_error("undefined variable: " + name);
                    }

                    globals.at(name) = peek(0);
                    break;
                }
                case OP::GET_LOCAL: {
                    u32 slot = READ_BYTE();
                    push(frame->slots[slot]);
                    break;
                }
                case OP::SET_LOCAL: {
                    u32 slot = READ_BYTE();
                    frame->slots[slot] = peek(0);
                    break;
                }
                case OP::GET_UPVALUE: {
                    u32 slot = READ_BYTE();
                    push(*(frame->closure->upvalues[slot]->location));
                    break;
                }
                case OP::SET_UPVALUE: {
                    u32 slot = READ_BYTE();
                    *(frame->closure->upvalues[slot]->location) = peek(0);
                    break;
                }
                case OP::CLOSE_UPVALUE:
                    closeUpvalues(stack_top - 1);
                    pop();
                    break;
                case OP::GET_PROPERTY: {
                    if (peek(0).held_type != Value::Type::INSTANCE) {
                        throw std::runtime_error("Only instances have properties.");
                    }

                    auto instance = std::get<std::shared_ptr<Instance>>(peek(0).value);
                    std::string name = std::get<std::string>(READ_CONSTANT().value);

                    if (instance->fields.find(name) != instance->fields.end()) {
                        pop(); // Instance.
                        push(instance->fields.at(name));
                        break;
                    }

                    if (!bindMethod(instance->klass, name)) {
                        return InterpretResult::RUNTIME_ERROR;
                    } else {
                        break;
                    }

                    throw std::runtime_error("Undefined property" + name + ".");
                    return InterpretResult::RUNTIME_ERROR;
                }
                case OP::SET_PROPERTY: {
                    if (peek(0).held_type != Value::Type::INSTANCE) {
                        throw std::runtime_error("Only instances have properties.");
                    }

                    auto instance = std::get<std::shared_ptr<Instance>>(peek(0).value);
                    instance->fields.insert({std::get<std::string>(READ_CONSTANT().value), peek(1)});
                    pop();
                    Value value = pop();
                    push(value);
                    break;
                }
                case OP::ADD: BINARY_OP(+); break;
                case OP::SUBTRACT: BINARY_OP(-); break;
                case OP::MULTIPLY: BINARY_OP(*); break;
                case OP::DIVIDE: BINARY_OP(/); break;
                case OP::POP: pop(); break;
                case OP::EQUAL: {
                    Value b = pop();
                    Value a = pop();

                    if (a.held_type == b.held_type && a.held_type == Value::Type::BOOL) {
                        bool result = std::get<bool>(a.value) == std::get<bool>(b.value);
                        push({.value = result, .held_type = Value::Type::BOOL});
                    } else if (a.held_type == b.held_type && a.held_type == Value::Type::INT) {
                        bool result = std::get<i64>(a.value) == std::get<i64>(b.value);
                        push({.value = result, .held_type = Value::Type::BOOL});
                    } else if (a.held_type == b.held_type && a.held_type == Value::Type::FLOAT) {
                        bool result = std::get<f64>(a.value) == std::get<f64>(b.value);
                        push({.value = result, .held_type = Value::Type::BOOL});
                    } else if (a.held_type == b.held_type && a.held_type == Value::Type::STRING) {
                        bool result = std::get<std::string>(a.value) == std::get<std::string>(b.value);
                        push({.value = result, .held_type = Value::Type::BOOL});
                    } else {
                        throw std::runtime_error("OP_EQUAL: 2 values have different type");
                    }

                    break;
                }
                case OP::GREATER: {
                    Value b = pop();
                    Value a = pop();

                    if (a.held_type == b.held_type && a.held_type == Value::Type::BOOL) {
                        /*bool result = std::get<bool>(a.value) == std::get<bool>(b.value);
                        push({.value = result, .held_type = Value::Type::BOOL});*/
                        throw std::runtime_error("cant do OP_GREATER with bools");
                    } else if (a.held_type == b.held_type && a.held_type == Value::Type::INT) {
                        bool result = std::get<i64>(a.value) > std::get<i64>(b.value);
                        push({.value = result, .held_type = Value::Type::BOOL});
                    } else if (a.held_type == b.held_type && a.held_type == Value::Type::FLOAT) {
                        bool result = std::get<f64>(a.value) > std::get<f64>(b.value);
                        push({.value = result, .held_type = Value::Type::BOOL});
                    } else if (a.held_type == b.held_type && a.held_type == Value::Type::STRING) {
                        throw std::runtime_error("cant do OP_GREATER with strings");
                    } else {
                        throw std::runtime_error("OP_GREATER 2 values have different type");
                    }

                    break;
                }
                case OP::LESS: {
                    Value b = pop();
                    Value a = pop();

                    if (a.held_type == b.held_type && a.held_type == Value::Type::BOOL) {
                        /*bool result = std::get<bool>(a.value) == std::get<bool>(b.value);
                        push({.value = result, .held_type = Value::Type::BOOL});*/
                        throw std::runtime_error("cant do OP_GREATER with bools");
                    } else if (a.held_type == b.held_type && a.held_type == Value::Type::INT) {
                        bool result = std::get<i64>(a.value) < std::get<i64>(b.value);
                        push({.value = result, .held_type = Value::Type::BOOL});
                    } else if (a.held_type == b.held_type && a.held_type == Value::Type::FLOAT) {
                        bool result = std::get<f64>(a.value) < std::get<f64>(b.value);
                        push({.value = result, .held_type = Value::Type::BOOL});
                    } else if (a.held_type == b.held_type && a.held_type == Value::Type::STRING) {
                        throw std::runtime_error("cant do OP_GREATER with strings");
                    } else {
                        throw std::runtime_error("OP_GREATER 2 values have different type");
                    }

                    break;
                }
                case OP::NOT: {
                    Value value = pop();
                    if (value.held_type != Value::Type::BOOL) {
                        throw std::runtime_error("cannot negate non bool type");
                    }
                    push({.value = !std::get<bool>(value.value), .held_type = Value::Type::BOOL});
                    break;
                }
                case OP::NEGATE: {
                    Value value = pop();
                    // push(-pop());
                    if (value.held_type == Value::Type::INT) {
                        push({.value = -std::get<i64>(value.value), .held_type = Value::Type::INT});
                    } else if (value.held_type == Value::Type::FLOAT) {
                        push({.value = -std::get<f64>(value.value), .held_type = Value::Type::FLOAT});
                    } else {
                        throw std::runtime_error("cannot negate this value");
                    }
                    break;
                }
                case OP::NIL: {
                    break;
                }
                case OP::RETURN: {
                    Value result = pop();
                    frames.pop_back();
                    closeUpvalues(frame->slots);
                    /*if (frames.size() == 1) {
                        return InterpretResult::OK;
                    }*/
                    stack_top = frame->slots;
                    push(result);
                    frame = &frames.back();
                    break;
                }
                case OP::PRINT: {
                    print_value(pop());
                    printf("\n");
                    break;
                }
                case OP::JUMP_IF_FALSE: {
                    u16 offset = READ_SHORT();
                    if (!std::get<bool>(peek(0).value)) {
                        frame->ip += offset;
                    }
                    break;
                }
                case OP::JUMP: {
                    u16 offset = READ_SHORT();
                    frame->ip += offset;
                    break;
                }
                case OP::LOOP: {
                    u16 offset = READ_SHORT();
                    frame->ip -= offset;
                    break;
                }
                case OP::CALL: {
                    i32 arg_count = static_cast<i32>(READ_BYTE());
                    if (!call_value(peek(arg_count), arg_count)) {
                        return InterpretResult::RUNTIME_ERROR;
                    }
                    frame = &frames.back();
                    break;
                }
                case OP::CLOSURE: {
                    auto function = std::get<std::shared_ptr<Closure>>(READ_CONSTANT().value)->function;
                    auto closure = std::make_shared<Closure>(function);
                    push({.value = closure, .held_type = Value::Type::CLOSURE});
                    for (u32 i = 0; i < closure->upvalues.size(); i++) {
                        u32 isLocal = READ_BYTE();
                        u32 index = READ_BYTE();
                        if (isLocal) {
                            closure->upvalues[i] = std::move(capture_Upvalue(frame->slots + index));
                        } else {
                            closure->upvalues[i] = std::move(frame->closure->upvalues[index]);
                        }
                    }
                    break;
                }
                case OP::CLASS:
                    push({.value = std::make_shared<Class>(std::get<std::string>(READ_CONSTANT().value)), .held_type = Value::Type::CLASS});
                    break;
                case OP::METHOD:
                    defineMethod(std::get<std::string>(READ_CONSTANT().value));
                    break;
                case OP::EOS: {
                    if (frames.size() == 1) {
                        return InterpretResult::OK;
                    }
                }
            }
        }
#undef READ_BYTE
#undef READ_CONSTANT
#undef BINARY_OP
#undef READ_SHORT
    }

    auto VM::interpret(const std::shared_ptr<Function> &script) -> InterpretResult {
        openUpvalues = std::make_unique<Upvalue_>();

        define_native("clock", [](u32 arg_count, Value *args) -> Value {
            f64 time = static_cast<f64>(clock()) / static_cast<f64>(CLOCKS_PER_SEC);
            return {.value = time, .held_type = Value::Type::FLOAT};
        });

        define_native("cpp_fn", [](u32 arg_count, Value *args) -> Value {
            std::cout << "cpp fn: " << std::get<std::string>(args[0].value) << std::endl;
            return {.value = 0, .held_type = Value::Type::INT};
        });

        define_native("cpp_add", [](u32 arg_count, Value *args) -> Value {
            return {.value = std::get<f64>(args[0].value) + std::get<f64>(args[1].value), .held_type = Value::Type::FLOAT};
        });

        push({.value = script, .held_type = Value::Type::FUNCTION});
        auto closure = std::make_shared<Closure>(script);
        pop();
        push({.value = closure, .held_type = Value::Type::CLOSURE});
        call_value({.value = closure, .held_type = Value::Type::CLOSURE}, 0);

        return run();
    }

    bool VM::call_value(const Value &callee, i32 arg_count) {
        if (callee.held_type == Value::Type::FUNCTION) {
            auto fn = std::get<std::shared_ptr<Function>>(callee.value);
            return call(std::make_shared<Closure>(fn), arg_count);
        } else if (callee.held_type == Value::Type::CLOSURE) {
            auto closure = std::get<std::shared_ptr<Closure>>(callee.value);
            return call(closure, arg_count);
        } else if (callee.held_type == Value::Type::NATIVE) {
            auto native = std::get<NativeFn>(callee.value);
            Value result = native(arg_count, stack_top - arg_count);
            stack_top -= arg_count + 1;
            push(result);
            return true;
        } else if (callee.held_type == Value::Type::CLASS) {
            auto klass = std::get<std::shared_ptr<Class>>(callee.value);
            stack_top[-arg_count - 1] = {.value = std::make_shared<Instance>(klass), .held_type = Value::Type::INSTANCE};
            if (klass->methods.find("init") != klass->methods.end()) {
                return call(std::get<std::shared_ptr<Closure>>(klass->methods.at("init").value), arg_count);
            }
            return true;
        } else if (callee.held_type == Value::Type::BOUND_METHOD) {
            auto bound = std::get<std::shared_ptr<BoundMethod>>(callee.value);
            stack_top[-arg_count - 1] = *(bound->reciever.get());
            return call(bound->method, arg_count);
        } else {
            throw std::runtime_error("Can only call functions and classes.");
            return false;
        }
    }

    bool VM::call(std::shared_ptr<Closure> closure, i32 arg_count) {
        if (static_cast<u32>(arg_count) != closure->function->arity) {
            throw std::runtime_error("Expected " + std::to_string(closure->function->arity) + " arguments but got " + std::to_string(arg_count));
            return false;
        }
        if (frames.size() == FRAMES_MAX) {
            throw std::runtime_error("Stack overflow.");
            return false;
        }

        frames.push_back({
            .closure = closure,
            .ip = closure->function->chunk->code.data(),
            .slots = stack_top - arg_count - 1,
        });

        return true;
    }

    void VM::define_native(const std::string &name, const NativeFn &function) {
        push({.value = name, .held_type = Value::Type::STRING});
        push({.value = function, .held_type = Value::Type::NATIVE});
        globals.insert({name, stack[1]});
        pop();
        pop();
    }

    auto VM::capture_Upvalue(Value *local) -> std::unique_ptr<Upvalue_> {
        std::unique_ptr<Upvalue_> prevUpvalue = NULL;
        std::unique_ptr<Upvalue_> upvalue = std::move(openUpvalues);
        while (upvalue != NULL && upvalue->location > local) {
            prevUpvalue = std::move(upvalue);
            upvalue = std::move(upvalue->next);
        }
        if (upvalue != NULL && upvalue->location == local) {
            return upvalue;
        }

        std::unique_ptr<Upvalue_> createdUpvalue = std::make_unique<Upvalue_>();
        createdUpvalue->location = local;
        createdUpvalue->next = std::move(upvalue);
        if (prevUpvalue == nullptr) {
            openUpvalues = std::move(createdUpvalue);
        } else {
            prevUpvalue->next = std::move(createdUpvalue);
        }
        return createdUpvalue;
    }

    void VM::closeUpvalues(Value *last) {
        while (openUpvalues != nullptr &&
               openUpvalues->location >= last) {
            std::unique_ptr<Upvalue_> upvalue = std::move(openUpvalues);
            upvalue->closed = *upvalue->location;
            upvalue->location = &upvalue->closed;
            openUpvalues = std::move(upvalue->next);
        }
    }

    void VM::defineMethod(const std::string &name) {
        Value method = peek(0);
        auto klass = std::get<std::shared_ptr<Class>>(peek(1).value);
        klass->methods.insert({name, method});
        pop();
    }

    bool VM::bindMethod(const std::shared_ptr<Class> &klass, const std::string &name) {
        if (klass->methods.find(name) == klass->methods.end()) {
            throw std::runtime_error("Undefined property " + name + ".");
        }
        Value method = klass->methods.at(name);

        auto bound = std::make_shared<BoundMethod>(peek(0), std::get<std::shared_ptr<Closure>>(method.value));
        pop();
        push(Value{.value = bound, .held_type = Value::Type::BOUND_METHOD});
        return true;
    }
} // namespace haflsl