add_library(core window.cc)

target_include_directories(core PUBLIC
  ${CMAKE_SOURCE_DIR}/external
  ${IMGUI_SRC}
  ${IMGUI_SRC}/backends
)

target_link_libraries(core PUBLIC
  glfw
  imgui
  implot
  OpenGL::OpenGL
)
