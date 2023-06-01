#include <haflsl/compiler/bytecode_compiler.hpp>
#include <haflsl/types.hpp>

#include <fstream>
#include <iostream>

namespace haflsl {
    BytecodeCompiler::BytecodeCompiler() {
        lexer = std::make_unique<Lexer>();
        parser = std::make_unique<Parser>();
        bytecode_writer = std::make_unique<BytecodeWriter>();
    }

    auto BytecodeCompiler::compile_from_source(const std::string &source) -> Result<Bytecode> {
        Global global {
            .file_processed = file_processed.empty() ? "unknown" : file_processed,
            .source = source
        };

        Result<std::vector<Token>> tokens = lexer->tokenize(global, source);
        if(tokens.is_err()) { return Result<Bytecode>(tokens.get_message()); }

        Result<std::vector<StatementPtr>> ast = parser->parse(global, tokens.get_value());
        if(ast.is_err()) { return Result<Bytecode>(ast.get_message()); }

        Result<std::shared_ptr<Function>> bytecode = bytecode_writer->compile(ast.get_value());
        if(bytecode.is_err()) { return Result<Bytecode>(bytecode.get_message()); }

        file_processed.clear();
        return Result<Bytecode>(Bytecode { .script = bytecode.get_value() });
    }

    auto BytecodeCompiler::compile_from_file(const std::filesystem::path &path) -> Result<Bytecode> {
        if(!std::filesystem::exists(path)) { return Result<Bytecode>("Couldn't find a file with path: " + path.string()); }
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
                return Result<Bytecode>("file with path: " + path.string() + " is empty.");
            }
        } else {
            return Result<Bytecode>("Couldn't read a file with path: " + path.string());
        }

        return compile_from_source(source);
    }
}