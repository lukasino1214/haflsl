#pragma once

#include <string>
#include <filesystem>

namespace HAFLSL {
    auto preprocessing(const std::string& source_code) -> std::string;
    auto preprocessing(const std::filesystem::path& file_path) -> std::string;
}