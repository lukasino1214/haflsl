cmake_minimum_required(VERSION 3.21)

include(cmake/warnings.cmake)
include(cmake/static_analysis.cmake)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

execute_process(
    COMMAND ${CMAKE_COMMAND} -E create_symlink
        ${CMAKE_BINARY_DIR}/compile_commands.json
        ${CMAKE_SOURCE_DIR}/compile_commands.json
)

project("haflsl-all")

add_subdirectory(haflsl)
add_subdirectory(examples)