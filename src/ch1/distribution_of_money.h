#pragma once
#define GLAD_GL_IMPLEMENTATION
#include "glad/gl.h"
#include <GLFW/glfw3.h>
#include <cstdint>

class DistributionOfMoney {
public:
  auto Run() -> void;
  auto InitWindow() -> void;
  auto InitWindow(uint32_t width, uint32_t height) -> void;
  auto InitPhysics() -> void;
  auto MainLoop() -> void;
  auto Cleanup() -> void;
  auto Window() -> GLFWwindow* { return m_window; }

private:
  GLFWwindow* m_window;
  uint32_t m_width = 800;
  uint32_t m_height= 600;
  auto KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode) -> void;
};
