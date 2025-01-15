#include "window.hh"
#include <iostream>

Window::Window(const std::string& window_name, i32 width, i32 height) :
  m_width(width), m_height(height) {
  glfwInit();

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  m_window = glfwCreateWindow(m_width, m_height, window_name.c_str(), nullptr, nullptr);
  if (m_window == nullptr) {
    std::cout << "Failed to create GLFW window!" << std::endl;
    return; 
  }

  glfwMakeContextCurrent(m_window);
  glfwSetWindowUserPointer(m_window, this);

  int version = gladLoadGL(glfwGetProcAddress);
  if (!version) {
    std::cout << "Failed to initialize GLAD!" << std::endl;
    return;
  }

  std::cout << "OpenGL version: " << GLAD_VERSION_MAJOR(version) << "." << GLAD_VERSION_MINOR(version) << std::endl;

  glad_glViewport(0, 0, m_width, m_height);
  glfwSetFramebufferSizeCallback(m_window, framebufferSizeCallback);
  glfwSetKeyCallback(m_window, keyCallback);


  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImPlot::CreateContext();
  ImGuiIO& io = ImGui::GetIO();
  io.Fonts->AddFontFromFileTTF("resources/JetBrainsMonoNLNerdFontMono-Regular.ttf", 20);
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

  ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 6.0f);
  ImGui::PushStyleVar(ImGuiStyleVar_GrabRounding, 6.0f);
  ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.0f);

  ImGui_ImplGlfw_InitForOpenGL(m_window, true);
  ImGui_ImplOpenGL3_Init();
}

auto Window::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode) -> void {
  Window* handler = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
  if (handler) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
      glfwSetWindowShouldClose(window, GL_TRUE);
    }
  }
}
auto Window::framebufferSizeCallback(GLFWwindow* window, int width, int height) -> void {
  glad_glViewport(0, 0, width, height);
}

auto Window::render(std::function<void()> physics, std::function<void()> plot) -> void {
  while (!glfwWindowShouldClose(m_window)) {
    glClearColor(0.2f, 0.4f, 0.8f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    physics();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport());

    plot();

    ImGui::Render();
    ImGui::EndFrame();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    glfwPollEvents();
    glfwSwapBuffers(m_window);
  }
}

