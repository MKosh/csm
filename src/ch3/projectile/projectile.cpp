#include <iostream>
#include "glad/gl.h"
#include "GLFW/glfw3.h"
#include "utils.h"
#include "ShaderProgram.hpp"

#include "projectile.h"

constexpr u32 WIDTH = 1280;
constexpr u32 HEIGHT= 720;

int main() {
  std::cout << "bang\n";

  if(!glfwInit()) {
    std::cerr << "Failed to init\n";
    return 1;
  }

  GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Projectile", nullptr, nullptr);

  if (!window) {
    std::cerr << "Failed to create window\n";
    return 1;
  }

  glfwMakeContextCurrent(window);
  int version = gladLoadGL(glfwGetProcAddress);

  ShaderProgram::Shader shaders[2] = { {GL_VERTEX_SHADER, "resources/shaders/ch3/projectile.vert"}, {GL_FRAGMENT_SHADER, "resources/shaders/ch3/projectile.frag"} };
  ShaderProgram shader_program{ shaders };

  if (version == 0) {
    std::cerr << "Failed to load gl\n";
    return 1;
  }

  float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
  };

  u32 VBO;
  glGenBuffers(1, &VBO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  glUseProgram(shader_program.ID);

  glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
  glViewport(0, 0, WIDTH, HEIGHT);

  while(!glfwWindowShouldClose(window)) {
    glClearColor(0.2f, 0.5f, 0.8f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawBuffer(VBO);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  std::cout << "hit\n";
  return 0;
}

auto framebufferSizeCallback(GLFWwindow* window, i32 width, i32 height) -> void {
  glViewport(0, 0, width, height);
}
