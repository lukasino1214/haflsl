#include <haflsl/compiler.hpp>
#include <haflsl/logger.hpp>
#include <haflsl/utils.hpp>
#include <haflsl/preprocessing.hpp>

namespace HAFLSL {
    auto create_compiler(const CompilerInfo& info) -> Compiler {
        if(info.show_debug_info) { Log::Init(); }
        return Compiler(info);
    }

    Compiler::Compiler(const CompilerInfo& info) {
        INFO("Starting the compiler");
    }

    void Compiler::compile(const std::string& file_path) {
        // read file to string
        //INFO("Opening a file: {:s}", file_path);
        //std::string text = read_file_to_string(file_path);
        /*INFO("Content of the file: \n{:s}", text);

        // content of file to vector of words
        std::vector<std::string> words = HAFLSL::string_to_words(text);
        std::string words_text = "";

        for(u32 i = 0; i < words.size(); i++) {
            if(i != words.size() - 1) {
                words_text += std::to_string(i) + ". word: " + words[i] + "\n";
            } else {
                words_text += std::to_string(i) + ". word: " + words[i];
            }
        }
        INFO("Separating content of file into vector of words: \n{:s}", words_text);

        // content of file to vector of lines
        std::vector<std::string> lines = HAFLSL::string_to_lines(text);
        std::string lines_text = "";

        for(u32 i = 0; i < lines.size(); i++) {
            if(i != lines.size() - 1) {
                lines_text += std::to_string(i) + ". line: " + lines[i] + "\n";
            } else {
                lines_text += std::to_string(i) + ". line: " + lines[i];
            }
        }
        INFO("Separating content of file into vector of lines: \n{:s}", lines_text);*/

        std::string processed = preprocessing(file_path);
        INFO("Preproccesed file: \n{:s}", processed);
    }
}