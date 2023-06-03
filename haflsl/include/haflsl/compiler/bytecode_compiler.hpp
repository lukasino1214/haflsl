#pragma once

#include <haflsl/result.hpp>
#include <haflsl/lexer.hpp>
#include <haflsl/parser.hpp>
#include <haflsl/writer/bytecode/bytecode_writer.hpp>

#include <filesystem>

namespace haflsl {
    struct Bytecode {
        std::shared_ptr<Function> script;
    };

    struct BytecodeCompiler {
        BytecodeCompiler();
        ~BytecodeCompiler() = default;

        [[nodiscard]] auto compile_from_source(const std::string& source) -> Result<Bytecode>;
        [[nodiscard]] auto compile_from_file(const std::filesystem::path& path) -> Result<Bytecode>;

    private:
        std::unique_ptr<Lexer> lexer;
        std::unique_ptr<Parser> parser;
        std::unique_ptr<BytecodeWriter> bytecode_writer;

        std::string file_processed = {};
    };
}