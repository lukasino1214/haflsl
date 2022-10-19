#pragma once

#include "token.hpp"
#include <vector>
#include <string>

namespace HAFLSL {
    namespace AST {
        void process(const std::vector<Token>& tokens, const std::string& src);
    }
}