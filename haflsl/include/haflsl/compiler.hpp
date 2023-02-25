#pragma once

#include "haflsl/types.hpp"

#include <filesystem>
#include <vector>
#include <string>

#include <haflsl/parser.hpp>

namespace HAFLSL {
    struct CompilerInfo {
        bool show_debug_info = false;
    };

    struct Compiler {
        //Compiler(const CompilerInfo& info);

        auto compile(const std::filesystem::path& file_path) -> std::vector<u32>;
        auto compile(const std::string& source_code) -> std::vector<u32>;

        auto get_spirv_dissambly(const std::vector<u32>& spirv) -> std::string;

        auto get_ast(const std::filesystem::path& file_path) -> AST;
        auto get_ast(const std::string& source_code) -> AST;

      private:
      Compiler(const CompilerInfo& info);
        friend auto create_compiler(const CompilerInfo& info) -> Compiler;
    };

    auto create_compiler(const CompilerInfo& info) -> Compiler;
}