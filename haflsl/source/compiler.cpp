#include <haflsl/compiler.hpp>
#include <haflsl/logger.hpp>
#include <haflsl/utils.hpp>
#include <haflsl/preprocessing.hpp>
#include <haflsl/lexer.hpp>
#include <haflsl/parser.hpp>

namespace HAFLSL {
    auto create_compiler(const CompilerInfo& info) -> Compiler {
        if(info.show_debug_info) { Log::Init(); }
        return Compiler(info);
    }

    Compiler::Compiler(const CompilerInfo& info) {
        INFO("Starting the compiler");
    }

    void Compiler::compile(const std::string& file_path) {
        std::string processed = preprocessing(file_path);
        INFO("Preproccesed file: \n{:s}", processed);
        Lexer lexer;
        std::vector<Token> tokens = lexer.tokenize(processed);
        /*INFO("Lexer found {} tokens!", tokens.size());
        INFO("Printing tokens from lexer");
        for(auto& token : tokens) {
            lexer.print_token(processed, token);
        }*/
        Parser parser;
        parser.parse(tokens);
    }
}