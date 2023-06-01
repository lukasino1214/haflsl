#include <iostream>

#include <haflsl/vm.hpp>
#include <haflsl/compiler/bytecode_compiler.hpp>

auto main() -> int {
    haflsl::BytecodeCompiler bytecode_compiler;
    auto result = bytecode_compiler.compile_from_file("test.test");

    haflsl::VM vm;
    vm.interpret(result.get_value().script);

    return 0;
}