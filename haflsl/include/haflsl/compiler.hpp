#pragma once

#include "haflsl/types.hpp"

#include <vector>
#include <string>

namespace HAFLSL {
    struct CompilerInfo {
        bool show_debug_info = false;
    };

    struct Compiler {
        auto compile(const std::string& file_path) -> std::vector<u32>;

      private:
        friend auto create_compiler(const CompilerInfo& info) -> Compiler; 
        Compiler(const CompilerInfo& info);
    };

    auto create_compiler(const CompilerInfo& info) -> Compiler; 
}