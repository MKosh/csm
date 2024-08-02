#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>
#include <GLFW/glfw3.h>

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

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, GL_TRUE);
  }
}

int main() {
  glfwInit();

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow* window = glfwCreateWindow(g_width, g_height, "Distribution of Money", nullptr, nullptr);
  if (window == nullptr) {
    std::cout << "Failed to create GLFW window!" << std::endl;
    return 0;
  }

  glfwMakeContextCurrent(window);

  int version = gladLoadGL(glfwGetProcAddress);
  if (!version) {
    std::cout << "Failed to initialize GLAD!" << std::endl;
    return 0;
  }
  std::cout << "OpenGL version: " << GLAD_VERSION_MAJOR(version) << "." << GLAD_VERSION_MINOR(version) << std::endl;

  glad_glViewport(0, 0, g_width, g_height);

  glfwSetKeyCallback(window, key_callback);

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImPlot::CreateContext();
  ImGuiIO& io = ImGui::GetIO();

  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init();

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

  while (!glfwWindowShouldClose(window)) {
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
    std::cout << "max: " << max << ", new max: " << new_max << '\n';

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    // ImGui::ShowDemoWindow();
    // if (ImGui::Begin("Plot")) {
      if (ImPlot::BeginPlot("Distribution of money", ImVec2(g_width-50,g_height-50))) {
        ImPlot::SetupAxes("Person","Money");
        // ImPlot::SetupAxesLimits(0,n_agents,0,max, ImPlotCond_Always);
        ImPlot::SetupAxisLimits(ImAxis_Y1, 0, max, ImPlotCond_Always);
        ImPlot::PlotLine("f(x)", m.data(), n_agents);
        ImPlot::SetNextMarkerStyle(ImPlotMarker_Circle);
        ImPlot::EndPlot();
      }
      // ImGui::End();
    // }
    // ImPlot::ShowDemoWindow();

    glClearColor(0.2f, 0.4f, 0.8f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    ImGui::Render();
    ImGui::EndFrame();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(window);
  }

  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImPlot::DestroyContext();
  ImGui::DestroyContext();
  glfwTerminate();

  return 0;
}
