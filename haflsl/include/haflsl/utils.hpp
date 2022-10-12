#pragma once

#include <string>
#include <vector>

namespace HAFLSL {
    std::string read_file_to_string(const std::string &filepath);
    std::vector<std::string> string_to_words(const std::string &content);
}