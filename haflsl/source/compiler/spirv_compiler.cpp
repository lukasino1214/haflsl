#include <haflsl/compiler/spirv_compiler.hpp>
#include <haflsl/types.hpp>

#include <fstream>
#include <iostream>

namespace haflsl {
    SpirvCompiler::SpirvCompiler() {
        lexer = std::make_unique<Lexer>();
        parser = std::make_unique<Parser>();
        spirv_writer = std::make_unique<SpirvWriter>();
    }

    auto SpirvCompiler::compile_from_source(const std::string &source) -> Result<SPIRV> {
        Global global {
            .file_processed = file_processed.empty() ? "unknown" : file_processed,
            .source = source
        };

        Result<std::vector<Token>> tokens = lexer->tokenize(global, source);
        if(tokens.is_err()) { return Result<SPIRV>(tokens.get_message()); }

        for(auto& t : tokens.get_value()) {
            t.print();
        }

        Result<std::vector<StatementPtr>> ast = parser->parse(global, tokens.get_value());
        if(ast.is_err()) { return Result<SPIRV>(ast.get_message()); }

        parser->debug_print(ast.get_value());

        Result<SPIRV> spirv_result = spirv_writer->compile(ast.get_value());
        if(spirv_result.is_err()) { return Result<SPIRV>(spirv_result.get_message()); }

        file_processed.clear();
        return Result<SPIRV>(spirv_result.get_value());
    }

    auto SpirvCompiler::compile_from_file(const std::filesystem::path &path) -> Result<SPIRV> {
        if(!std::filesystem::exists(path)) { return Result<SPIRV>("Couldn't find a file with path: " + path.string()); }
        file_processed = path.string();

        std::string source;
        std::ifstream in(path.c_str(), std::ios::in | std::ios::binary);
        if (in) {
            in.seekg(0, std::ios::end);
            u32 size = static_cast<u32>(in.tellg());
            if (size != 0) {
                source.resize(size);
                in.seekg(0, std::ios::beg);
                in.read(source.data(), size);
            } else {
                return Result<SPIRV>("file with path: " + path.string() + " is empty.");
            }
        } else {
            return Result<SPIRV>("Couldn't read a file with path: " + path.string());
        }

        return compile_from_source(source);
    }
}