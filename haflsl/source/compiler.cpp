#include <haflsl/compiler.hpp>

namespace HAFLSL {
    auto create_compiler(const CompilerInfo& info) -> Compiler {
        return Compiler(info);
    }

    auto Compiler::compile(const std::string& file_path) -> std::vector<u32> {
        
    }
}