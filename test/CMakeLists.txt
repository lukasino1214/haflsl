cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Test)
add_executable(Test "main.cpp")
target_link_libraries(Test PRIVATE HAFLSL)