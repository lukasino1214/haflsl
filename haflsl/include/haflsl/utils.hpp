#pragma once

#include <string>
#include <vector>

namespace HAFLSL {
    auto read_file_to_string(const std::string &file_path) -> std::string;
    auto string_to_words(const std::string &content) -> std::vector<std::string>;
    auto string_to_lines(const std::string &content) -> std::vector<std::string>;
}