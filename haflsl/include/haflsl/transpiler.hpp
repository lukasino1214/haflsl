#pragma once
#include "parser.hpp"

namespace HAFLSL {
    struct Transpiler {
        Transpiler() = default;
        ~Transpiler() = default;

        auto convert_ast_to_spirv(const AST& ast, const std::string_view& entrypoint_name) -> std::vector<u32>;
    };
}