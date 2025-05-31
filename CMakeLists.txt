cmake_minimum_required(VERSION 3.24)

set(CMAKE_EXPORT_COMPILE_COMMANDS on)

project(test LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_COMPILER clang++)
# set(GLFW_INCLUDE_NONE)
include(FetchContent)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

find_package(imgui QUIET)

if (NOT TARGET imgui::imgui)
  message(STATUS "--- IMGUI not found on system. Fetching content")
  FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG v1.91.0-docking
  )
  FetchContent_MakeAvailable(imgui)
  set(IMGUI_SRC "${CMAKE_BINARY_DIR}/_deps/imgui-src")
endif()

find_package(implot QUIET)

if (NOT TARGET implot::implot)
  FetchContent_Declare(
    implot
    GIT_REPOSITORY https://github.com/epezent/implot
    GIT_TAG f156599faefe316f7dd20fe6c783bf87c8bb6fd9
  )
  FetchContent_MakeAvailable(implot)
  set(IMPLOT_SRC "${CMAKE_BINARY_DIR}/_deps/implot-src")
endif()

add_subdirectory(src)
add_subdirectory(external)
