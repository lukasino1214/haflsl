#include "haflsl/transpiler.hpp"
#include <haflsl/compiler.hpp>
#include <haflsl/logger.hpp>
#include <haflsl/utils.hpp>
#include <haflsl/preprocessing.hpp>
#include <haflsl/lexer.hpp>
#include <haflsl/parser.hpp>
#include <haflsl/transpiler.hpp>

#include <spirv-tools/libspirv.hpp>
#include <spirv-tools/optimizer.hpp>

namespace HAFLSL {
    auto create_compiler(const CompilerInfo& info) -> Compiler {
        if(info.show_debug_info) { Log::Init(); }
        return Compiler(info);
    }

    Compiler::Compiler(const CompilerInfo& info) {
        INFO("Starting the compiler");
    }

    auto Compiler::compile(const std::filesystem::path& file_path) -> std::vector<u32> {
        std::string source_code = read_file_to_string(file_path.generic_string());
        return compile(source_code);
    }

    auto Compiler::compile(const std::string& source_code) -> std::vector<u32> {
        std::string processed = preprocessing(source_code);
        //INFO("Preproccesed file: \n{:s}", processed);
        Lexer lexer;
        std::vector<Token> tokens = lexer.tokenize(processed);
        //INFO("Lexer found {} tokens!", tokens.size());
        //INFO("Printing tokens from lexer");
        /*for(auto& token : tokens) {
            lexer.print_token(processed, token);
        }*/
        Parser parser;
        AST ast = parser.parse(tokens);
        parser.print_debug_ast(ast);

        Transpiler transpiler;
        return transpiler.convert_ast_to_spirv(ast, "main");
    }

    auto Compiler::get_spirv_dissambly(const std::vector<u32>& spirv) -> std::string {
        spvtools::SpirvTools core(SPV_ENV_UNIVERSAL_1_3);
        std::string spirv_disassmbly = {};

        core.Disassemble(spirv, &spirv_disassmbly);

        std::vector<std::string> lines = string_to_lines(spirv_disassmbly);

        std::vector<u32> first_op = {};
        u32 biggest_offset = 0;

        for(auto& line : lines) {
            for(u32 i = 0; i < line.size(); i++) {
                if(line[i] == 'O' && line[i+1] == 'p') {
                    first_op.push_back(i);
                    if(i > biggest_offset) {
                        biggest_offset = i;
                    }
                    break;
                }
            }
        }

        for(u32 i = 0; i < lines.size(); i++) {
            std::string spaces = "";
            u32 length_spaces = (biggest_offset - 3) - (first_op[i] - 3);
            for(u32 j = 0; j < length_spaces; j++) { spaces += " "; }

            lines[i] = spaces + lines[i];
        }

        spirv_disassmbly = lines_to_string(lines);

        return spirv_disassmbly;
    }

    auto Compiler::get_ast(const std::filesystem::path &file_path) -> AST {
        std::string source_code = read_file_to_string(file_path.generic_string());
        return get_ast(source_code);
    }

    auto Compiler::get_ast(const std::string& source_code) -> AST {
        std::string processed = preprocessing(source_code);

        Lexer lexer;
        std::vector<Token> tokens = lexer.tokenize(processed);

        Parser parser;
        AST ast = parser.parse(tokens);
        return ast;
    }
}