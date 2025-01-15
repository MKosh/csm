add_executable(ComparingEulerAlgorithms ComparingEulerAlgorithms.cc)

message(STATUS "src dir ${CMAKE_SOURCE_DIR}")
target_include_directories(ComparingEulerAlgorithms PUBLIC
  ${CMAKE_SOURCE_DIR}/external
  ${CMAKE_SOURCE_DIR}/src
  ${IMGUI_SRC}
  ${IMGUI_SRC}/backends
)

target_link_libraries(ComparingEulerAlgorithms PUBLIC
  glfw
  imgui
  implot
  OpenGL::OpenGL
  core
)
