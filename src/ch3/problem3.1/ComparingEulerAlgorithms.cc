#include "imgui.h"
#include "imgui_impl_glfw.h"
#define GLAD_GL_IMPLEMENTATION
#include "ComparingEulerAlgorithms.hh"
#include <iostream>
#include <cmath>
#include <algorithm>


std::vector<double> xs(1000);
std::vector<double> ys(1000);

auto fn() -> void {
  for (int i = 0; i < xs.size(); i++) {
    ys[i] = std::sin(xs[i] + glfwGetTime());
  }
}

auto plot() -> void {
  ImGuiIO& io = ImGui::GetIO();
  ImGui::Begin("Simulation");
  ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
  if (ImPlot::BeginPlot("thingy", ImVec2(-1,-1))) {
    ImPlot::SetupAxes("x", "y");
    ImPlot::PlotLine("sin", xs.data(), ys.data(), 1000);
    ImPlot::EndPlot();
  }
  ImGui::End();
}

int main() {
  std::cout << "Hello problem 3.1" << std::endl;
  Window window{"wow", 800, 600};

  std::generate(xs.begin(), xs.end(), [n = -500] () mutable {return n++ * 0.02;});

  window.render(fn, plot);

}
