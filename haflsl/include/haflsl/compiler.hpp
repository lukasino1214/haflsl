#pragma once

#include "haflsl/types.hpp"

#include <vector>
#include <string>

namespace HAFLSL {
    struct CompilerInfo {
        bool show_debug_info = false;
    };

    struct Compiler {
        //Compiler(const CompilerInfo& info);

        void compile(const std::string& file_path);

      private:
      Compiler(const CompilerInfo& info);
        friend auto create_compiler(const CompilerInfo& info) -> Compiler;
    };

    auto create_compiler(const CompilerInfo& info) -> Compiler;
}