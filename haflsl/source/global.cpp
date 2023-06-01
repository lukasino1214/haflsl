#include <haflsl/global.hpp>
#include <iostream>

namespace haflsl {
    auto Global::make_error_message(u32 line, u32 column, const std::string& error_message) const -> std::string {
        auto spaces = [](u32 size) -> std::string {
            std::string space = "";
            for(u32 i = 0; i < size; i++) { space += " "; }
            return space;
        };


        std::string extracted_line = "something went wrong";
        i32 starting_index = -1;
        i32 current_line = 1;
        for(u32 i = 0; i < source.size(); i++) {
            if(current_line == line && starting_index == -1) { starting_index = i; }
            if(current_line - 1 == line) { 
                std::cout << "starting index: " << starting_index << " len: " << i - starting_index << std::endl;
                extracted_line = source.substr(starting_index, i - starting_index - 1); 
                break;
            }
            if(source[i] == '\n') { current_line++; }
        }

        std::string line_error = std::to_string(line);

        std::string error = "error: " + error_message + '\n';
        error += spaces(line_error.size()) + "--> " + file_processed + ":" + std::to_string(line) + ":" + std::to_string(column) + '\n';
        error += spaces(line_error.size()) + " | " + '\n';
        error += line_error + " | " + extracted_line + '\n';
        error += spaces(line_error.size()) + " | "  + spaces(column-1) + "^ " + error_message;

        return error;
    }
}