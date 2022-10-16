cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_TOOLCHAIN_FILE "/home/lukas/vcpkg/scripts/buildsystems/vcpkg.cmake")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

execute_process(
    COMMAND ${CMAKE_COMMAND} -E create_symlink
        ${CMAKE_BINARY_DIR}/compile_commands.json
        ${CMAKE_SOURCE_DIR}/compile_commands.json
)

project(CompilerLib)

find_package(spdlog CONFIG REQUIRED)

add_subdirectory(haflsl)
add_subdirectory(test)