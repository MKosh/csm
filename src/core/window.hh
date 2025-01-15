#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "implot.h"

#include <string>
#include <functional>

#include "utils.h"


class Window {
public:
  Window();
  Window(const std::string& window_name = "Window", i32 width = 800, i32 height = 600);
  auto initWindow(i32 width = 800, i32 height = 600) -> void;
  auto getWindow() -> GLFWwindow* { return m_window; }
  auto render(std::function<void()> physics, std::function<void()> plot) -> void;

private:
  GLFWwindow* m_window;
  i32 m_width = 800;
  i32 m_height= 600;
  static auto keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode) -> void;
  static auto framebufferSizeCallback(GLFWwindow* window, int width, int height) -> void;
};

