#pragma once

#include <vector>
#include <string_view>

#include <haflsl/types.hpp>
#include <haflsl/token.hpp>
#include <haflsl/value.hpp>

namespace haflsl {
    enum struct OP : u32 {
        CONSTANT,
        DEFINE_GLOBAL,
        GET_GLOBAL,
        SET_GLOBAL,
        GET_LOCAL,
        SET_LOCAL,
        GET_UPVALUE,
        SET_UPVALUE,
        CLOSE_UPVALUE,
        GET_PROPERTY,
        SET_PROPERTY,
        ADD,
        SUBTRACT,
        MULTIPLY,
        DIVIDE,
        POP,
        EQUAL,
        GREATER,
        LESS,
        NOT,
        NEGATE,
        RETURN,
        PRINT,
        JUMP,
        JUMP_IF_FALSE,
        LOOP,
        CALL,
        CLOSURE,
        NIL,
        CLASS,
        METHOD,
        EOS
    };

    struct Function;
    struct Chunk {
        Chunk() = default;
        ~Chunk() = default;

        void write(OP op, u32 line);
        void write(u32 byte, u32 line);

        u32 add_constant(const Token &token);
        u32 add_constant(const std::shared_ptr<Function> &function);
        u32 add_constant(const std::shared_ptr<Closure> &closure);

        void disassemble(const std::string_view &name);

        std::vector<u32> code;
        std::vector<u32> lines;
        std::vector<Value> constants;

      private:
        auto simple_instruction(const std::string_view &name, u32 offset) -> u32;
        auto constant_instruction(const std::string_view &name, u32 offset) -> u32;
        auto byte_instruction(const std::string_view &name, u32 offset) -> i32;
        auto disassemble_instruction(u32 offset) -> u32;
        auto jump_instruction(const std::string_view &name, i32 sign, u32 offset) -> i32;

        friend struct VM;
    };
} // namespace haflsl