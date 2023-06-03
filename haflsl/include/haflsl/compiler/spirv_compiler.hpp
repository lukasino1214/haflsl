#pragma once

#include <haflsl/result.hpp>
#include <haflsl/lexer.hpp>
#include <haflsl/parser.hpp>
#include <haflsl/writer/spirv/spirv_writer.hpp>

#include <filesystem>

namespace haflsl {
    struct SpirvCompiler {
        SpirvCompiler();
        ~SpirvCompiler() = default;

        [[nodiscard]] auto compile_from_source(const std::string& source) -> Result<SPIRV>;
        [[nodiscard]] auto compile_from_file(const std::filesystem::path& path) -> Result<SPIRV>;

    private:
        std::unique_ptr<Lexer> lexer;
        std::unique_ptr<Parser> parser;
        std::unique_ptr<SpirvWriter> spirv_writer;

        std::string file_processed = {};
    };
}