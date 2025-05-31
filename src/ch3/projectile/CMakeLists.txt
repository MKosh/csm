add_executable(projectile projectile.cpp ShaderProgram.cpp)

target_include_directories(projectile PUBLIC
  ${CMAKE_SOURCE_DIR}/external/glad/include
  ${CMAKE_SOURCE_DIR}/src/core
)

target_link_libraries(projectile PUBLIC
  glad
  OpenGL
  glfw
)
