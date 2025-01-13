add_executable(test test.cxx)

target_include_directories(test PUBLIC
    # ${CMAKE_SOURCE_DIR}/external
    # $ENV{IMGUI}
    # $ENV{IMGUI}/include
    # $ENV{IMGUI}/include/imgui
    # $ENV{IMGUI}/include/imgui/backends
  ${CMAKE_SOURCE_DIR}/external
  ${IMGUI_SRC}
  ${IMGUI_SRC}/backends
)

target_link_directories(test PUBLIC
  ${IMGUI_SRC}
  ${IMGUI_SRC}/backends
)
target_link_libraries(test PUBLIC
    glfw
    imgui
    OpenGL::OpenGL
)

add_subdirectory(ch1)
add_subdirectory(ch3)
