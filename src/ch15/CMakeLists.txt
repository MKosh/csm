add_executable(ising ising_model.cc)

target_include_directories(ising PUBLIC
  ${CMAKE_SOURCE_DIR}/external
  ${CMAKE_SOURCE_DIR}/src
  ${IMGUI_SRC}
  ${IMGUI_SRC}/backends
  ${IMPLOT_SRC}
)

target_link_libraries(ising PUBLIC
  glad
  glfw
  imgui
  implot
  OpenGL::OpenGL
  core
)

