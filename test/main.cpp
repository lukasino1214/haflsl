#include <iostream>
#include <haflsl/compiler.hpp>

int main() {
    HAFLSL::Compiler compiler = HAFLSL::create_compiler({
        .show_debug_info = true
    });

    std::vector<uint32_t> code = compiler.compile("test.txt");

    return 0;
}
