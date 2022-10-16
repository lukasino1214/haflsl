#include <haflsl/compiler.hpp>
#include <haflsl/logger.hpp>
#include <haflsl/utils.hpp>
#include <haflsl/preprocessing.hpp>
#include <haflsl/lexer.hpp>

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
        std::vector<Token> tokens = Lexer::tokenize(processed);
        INFO("Printing tokens from lexer");
        for(auto& token : tokens) {
            Lexer::print_token(processed, token);
        }
    }
}