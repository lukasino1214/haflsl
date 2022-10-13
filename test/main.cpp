#include <iostream>
#include <haflsl/compiler.hpp>

int main() {
    HAFLSL::Compiler compiler = HAFLSL::create_compiler({
        .show_debug_info = true
    });

    compiler.compile("test.txt");

    return 0;
}