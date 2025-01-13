add_executable(ComparingEulerAlgorithms ComparingEulerAlgorithms.cc)

target_link_libraries(ComparingEulerAlgorithms PUBLIC
  glfw
  imgui
  implot
  OpenGL::OpenGL
)
