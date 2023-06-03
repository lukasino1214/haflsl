#include <haflsl/compiler/spirv_compiler.hpp>

#include <spirv-tools/libspirv.h>
#include <spirv-tools/libspirv.hpp>
#include <spirv-tools/optimizer.hpp>

#include <iostream>

int main() {
    auto spirv_compiler = haflsl::SpirvCompiler();
    auto spirv = spirv_compiler.compile_from_file("draw.test");

    spvtools::SpirvTools core(SPV_ENV_UNIVERSAL_1_3);

    auto print_msg_to_stderr = [](spv_message_level_t, const char *, const spv_position_t &, const char *m) {
        std::cerr << "spirv validator error: " << m << std::endl;
    };

    core.SetMessageConsumer(print_msg_to_stderr);

    std::string spirv_disassmble = {};

    core.Disassemble(spirv.get_value(), &spirv_disassmble);

    std::cout << spirv_disassmble << std::endl;
    core.Validate(spirv.get_value());

    return 0;
}