cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#High As Fuck Lukas Shader Language
project(HAFLSL)

add_library(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE source/utils.cpp source/compiler.cpp source/logger.cpp source/preprocessing.cpp source/lexer.cpp source/parser.cpp source/transpiler.cpp source/code_buffer.cpp include/haflsl/uuid.hpp source/uuid.cpp )
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC spdlog::spdlog spdlog::spdlog_header_only FastFloat::fast_float)
target_link_libraries(${PROJECT_NAME} PRIVATE SPIRV-Tools-static)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
           $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    )

install(
    TARGETS ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}-config
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(
    EXPORT ${PROJECT_NAME}-config
    NAMESPACE ${PROJECT_NAME}::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)

install(
    DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/include/${PROJECT_NAME}/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}
)