#include "distribution_of_money.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "implot.h"

#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdint>
#include <vector>
#include <random>
#include <numeric>
#include <algorithm>


const float m_0 = 1000.f;
const size_t n_agents = 100;

auto DistributionOfMoney::FramebufferSizeCallback(GLFWwindow* window, int width, int height) -> void
{
  glad_glViewport(0, 0, width, height);
}

auto DistributionOfMoney::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode) -> void
{
  DistributionOfMoney* handler = reinterpret_cast<DistributionOfMoney*>(glfwGetWindowUserPointer(window));
  if (handler) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
      glfwSetWindowShouldClose(window, GL_TRUE);
    }
  }
}

auto DistributionOfMoney::InitWindow(uint32_t width, uint32_t height) -> void
{
  m_width = width;
  m_height = height;

  glfwInit();

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  m_window = glfwCreateWindow(m_width, m_height, "Distribution of Money", nullptr, nullptr);
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
  glfwSetFramebufferSizeCallback(m_window, FramebufferSizeCallback);
  glfwSetKeyCallback(m_window, KeyCallback);

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

auto DistributionOfMoney::Run() -> void
{
  std::vector<float> m(n_agents, m_0);

  std::mt19937 mt{ std::random_device{}() };
  std::uniform_real_distribution<float> random_epsilon;
  std::uniform_int_distribution<> random_agent{0, n_agents - 1};

  int32_t agent_i = -1;
  int32_t agent_j = -1;
  float m_i = -1.f;
  float m_j = -1.f;
  float epsilon = -1.f;
  std::vector<size_t> xs(n_agents);
  std::iota(xs.begin(), xs.end(), 0);
  float max = 0;
  float new_max = 0;
  float delta_m = 0.f;
  float lambda = 0.f;

  while (!glfwWindowShouldClose(m_window)) {
    glfwPollEvents();
    glClearColor(0.2f, 0.4f, 0.8f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    if (m_running == true) {
      agent_i = random_agent(mt);
      agent_j = random_agent(mt);
      m_i = m.at(agent_i);
      m_j = m.at(agent_j);
      epsilon = random_epsilon(mt);

      delta_m = (1 - lambda) * (epsilon * m_j - (1 - epsilon) * m_i);
      m.at(agent_i) = m_i + delta_m;
      m.at(agent_j) = m_j - delta_m;

      new_max = *std::max_element(m.begin(), m.end());
      max = std::max(max, new_max);
    }

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport());
    ImGui::Begin("Simulation");
    ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
    ImGui::SliderFloat("Lambda", &lambda, 0.0f, 1.0f);
    if (ImGui::Button("Start/Stop")) {
      m_running = !m_running;
    }
    if (ImPlot::BeginPlot("Distribution of money", ImVec2(-1,-1))) {
      ImPlot::SetupAxes("Person","Money");
      ImPlot::SetupAxisLimits(ImAxis_Y1, 0, max, ImPlotCond_Always);
      ImPlot::PlotLine("f(x)", m.data(), n_agents);
      ImPlot::SetNextMarkerStyle(ImPlotMarker_Circle);
      ImPlot::EndPlot();
    }
    ImGui::End();

    ImGui::Render();
    ImGui::EndFrame();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(m_window);
  }
}

auto DistributionOfMoney::Cleanup() -> void
{
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImPlot::DestroyContext();
  ImGui::DestroyContext();
  glfwTerminate();
}

