#include <haflsl/chunk.hpp>

#include <iostream>

namespace haflsl {
    void Chunk::write(OP op, u32 line) {
        code.push_back(static_cast<u32>(op));
        lines.push_back(line);
    }

    void Chunk::write(u32 byte, u32 line) {
        code.push_back(byte);
        lines.push_back(line);
    }

    auto Chunk::add_constant(const Token &token) -> u32 {
        Value value{};
        if (token.type == TokenType::BOOL_CONSTANT) {
            value.held_type = Value::Type::BOOL;
            value.value = std::get<bool>(token.value);
        } else if (token.type == TokenType::INT_CONSTANT) {
            value.held_type = Value::Type::INT;
            value.value = std::get<i64>(token.value);
        } else if (token.type == TokenType::FLOAT_CONSTANT) {
            value.held_type = Value::Type::FLOAT;
            value.value = std::get<f64>(token.value);
        } else if (token.type == TokenType::STRING_CONSTANT) {
            value.held_type = Value::Type::STRING;
            value.value = std::get<std::string>(token.value);
        } else if (token.type == TokenType::IDENTIFIER) {
            value.held_type = Value::Type::STRING;
            value.value = std::get<std::string>(token.value);
        }

        constants.push_back(value);
        return static_cast<u32>(constants.size()) - 1;
    }

    u32 Chunk::add_constant(const std::shared_ptr<Function> &function) {
        constants.push_back({.value = function, .held_type = Value::Type::FUNCTION});
        return static_cast<u32>(constants.size()) - 1;
    }

    u32 Chunk::add_constant(const std::shared_ptr<Closure> &closure) {
        constants.push_back({.value = closure, .held_type = Value::Type::CLOSURE});
        return static_cast<u32>(constants.size()) - 1;
    }

    auto Chunk::simple_instruction(const std::string_view &name, u32 offset) -> u32 {
        std::cout << name.data() << std::endl;
        return offset + 1;
    }

    auto Chunk::constant_instruction(const std::string_view &name, u32 offset) -> u32 {
        u32 constant = code[offset + 1];
        printf("%-16s %4d '", name.data(), constant);
        print_value(constants[constant]);
        printf("'\n");
        return offset + 2;
    }

    auto Chunk::byte_instruction(const std::string_view &name, u32 offset) -> i32 {
        u32 slot = code[offset + 1];
        printf("%-16s %4d\n", name.data(), slot);
        return offset + 2;
    }

    auto Chunk::jump_instruction(const std::string_view &name, i32 sign, u32 offset) -> i32 {
        u16 jump = (uint16_t)(code[offset + 1] << 8);
        jump |= code[offset + 2];
        printf("%-16s %4d -> %d\n", name.data(), offset, offset + 3 + sign * jump);
        return offset + 3;
    }

    auto Chunk::disassemble_instruction(u32 offset) -> u32 {
        printf("%04d ", offset);
        if (offset > 0 &&
            lines[offset] == lines[offset - 1]) {
            printf(" | ");
        } else {
            printf("%4d ", lines[offset]);
        }

        OP instruction = static_cast<OP>(code[offset]);
        switch (instruction) {
            case OP::CONSTANT: return constant_instruction("OP_CONSTANT", offset);
            case OP::DEFINE_GLOBAL: return constant_instruction("OP_DEFINE_GLOBAL", offset);
            case OP::GET_GLOBAL: return constant_instruction("OP_GET_GLOBAL", offset);
            case OP::SET_GLOBAL: return constant_instruction("OP_SET_GLOBAL", offset);
            case OP::GET_LOCAL: return byte_instruction("OP_GET_LOCAL", offset);
            case OP::SET_LOCAL: return byte_instruction("OP_SET_LOCAL", offset);
            case OP::GET_UPVALUE: return byte_instruction("OP_GET_UPVALUE", offset);
            case OP::SET_UPVALUE: return byte_instruction("OP_SET_UPVALUE", offset);
            case OP::CLOSE_UPVALUE: return simple_instruction("OP_CLOSE_UPVALUE", offset);
            case OP::GET_PROPERTY: return constant_instruction("OP_GET_PROPERTY", offset);
            case OP::SET_PROPERTY: return constant_instruction("OP_SET_PROPERTY", offset);
            case OP::ADD: return simple_instruction("OP_ADD", offset);
            case OP::SUBTRACT: return simple_instruction("OP_SUBTRACT", offset);
            case OP::MULTIPLY: return simple_instruction("OP_MULTIPLY", offset);
            case OP::DIVIDE: return simple_instruction("OP_DIVIDE", offset);
            case OP::POP: return simple_instruction("OP_POP", offset);
            case OP::EQUAL: return simple_instruction("OP_EQUAL", offset);
            case OP::GREATER: return simple_instruction("OP_GREATER", offset);
            case OP::LESS: return simple_instruction("OP_LESS", offset);
            case OP::NOT: return simple_instruction("OP_NOT", offset);
            case OP::NEGATE: return simple_instruction("OP_NEGATE", offset);
            case OP::RETURN: return simple_instruction("OP_RETURN", offset);
            case OP::PRINT: return simple_instruction("OP_PRINT", offset);
            case OP::JUMP: return jump_instruction("OP_JUMP", 1, offset);
            case OP::JUMP_IF_FALSE: return jump_instruction("OP_JUMP_IF_FALSE", 1, offset);
            case OP::LOOP: return jump_instruction("OP_LOOP", -1, offset);
            case OP::CALL: return byte_instruction("OP_CALL", offset);
            case OP::CLASS: return constant_instruction("OP_CLASS", offset);
            case OP::METHOD: return constant_instruction("OP_METHOD", offset);
            case OP::CLOSURE: {
                offset++;
                u32 constant = code[offset++];
                printf("%-16s %4d ", "OP_CLOSURE", constant);
                print_value(constants[constant]);
                printf("\n");

                // ObjFunction *function = AS_FUNCTION(constants[constant]);
                auto function = std::get<std::shared_ptr<Closure>>(constants[constant].value)->function;
                for (int j = 0; j < function->upvalue_count; j++) {
                    int isLocal = code[offset++];
                    int index = code[offset++];
                    printf("%04d | %s %d\n",
                           offset - 2, isLocal ? "local" : "upvalue", index);
                }

                return offset;
            }
            case OP::EOS: return simple_instruction("OP_EOS", offset);
            case OP::NIL: return simple_instruction("OP_NIL", offset);
            default:
                std::cout << "Unknown opcode " << static_cast<u32>(instruction) << std::endl;
                return offset + 1;
        }
    }

    void Chunk::disassemble(const std::string_view &name) {
        std::cout << "== " << name.data() << " == " << std::endl;

        for (u32 offset = 0; offset < code.size();) {
            offset = disassemble_instruction(offset);
        }
    }
} // namespace haflsl