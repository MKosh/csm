cmake_minimum_required(VERSION 3.24)

set(CMAKE_EXPORT_COMPILE_COMMANDS on)

project(test LANGUAGES CXX)

set(CMAKE_CXX_COMPILER clang++)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

add_subdirectory(src)
add_subdirectory(external)
