cmake_minimum_required(VERSION 3.24)

set(CMAKE_EXPORT_COMPILE_COMMANDS on)

project(test LANGUAGES CXX)

add_subdirectory(src)
add_subdirectory(external)
