#pragma once 

#include <haflsl/types.hpp>

#include <string>

namespace haflsl {
    struct Global {
        std::string file_processed;
        std::string source;

        auto make_error_message(u32 line, u32 column, const std::string& error_message) const -> std::string;
    };
}