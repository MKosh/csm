#include "distribution_of_money.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "implot.h"

#include <iostream>
#include <cstdint>
#include <vector>
#include <random>
#include <numeric>
#include <algorithm>


const uint32_t g_width = 800;
const uint32_t g_height= 600;
const float m_0 = 1000.f;
const size_t n_agents = 100;

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

  int version = gladLoadGL(glfwGetProcAddress);
  if (!version) {
    std::cout << "Failed to initialize GLAD!" << std::endl;
    return;
  }
  std::cout << "OpenGL version: " << GLAD_VERSION_MAJOR(version) << "." << GLAD_VERSION_MINOR(version) << std::endl;

  glad_glViewport(0, 0, m_width, m_height);

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImPlot::CreateContext();
  ImGuiIO& io = ImGui::GetIO();

  ImGui_ImplGlfw_InitForOpenGL(m_window, true);
  ImGui_ImplOpenGL3_Init();
  
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, GL_TRUE);
  }
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

  while (!glfwWindowShouldClose(m_window)) {
    glfwPollEvents();

    agent_i = random_agent(mt);
    agent_j = random_agent(mt);
    m_i = m.at(agent_i);
    m_j = m.at(agent_j);
    epsilon = random_epsilon(mt);

    m.at(agent_i) = epsilon * (m_i + m_j);
    m.at(agent_j) = (1 - epsilon) * (m_i + m_j);

    new_max = *std::max_element(m.begin(), m.end());
    max = std::max(max, new_max);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    if (ImPlot::BeginPlot("Distribution of money", ImVec2(g_width-50,g_height-50))) {
      ImPlot::SetupAxes("Person","Money");
      ImPlot::SetupAxisLimits(ImAxis_Y1, 0, max, ImPlotCond_Always);
      ImPlot::PlotLine("f(x)", m.data(), n_agents);
      ImPlot::SetNextMarkerStyle(ImPlotMarker_Circle);
      ImPlot::EndPlot();
    }

    glClearColor(0.2f, 0.4f, 0.8f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

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

int main() {
  DistributionOfMoney simulation;
  simulation.InitWindow(g_width, g_height);
  simulation.Run();
  simulation.Cleanup();

  return 0;
}

