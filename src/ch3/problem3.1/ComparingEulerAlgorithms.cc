#include "imgui.h"
#include "imgui_impl_glfw.h"
#define GLAD_GL_IMPLEMENTATION
#include "ComparingEulerAlgorithms.hh"
#include <iostream>
#include <iomanip>

auto fn() -> void {
  /*ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);*/
  /*std::cout << "FPS: " << std::fixed << std::setprecision(1) << ImGui::GetIO().Framerate << "\n";*/
}

auto plot() -> void {
    ImGui::Begin("Simulation");
    if (ImPlot::BeginPlot("thingy", ImVec2(-1,-1))) {
      ImPlot::SetupAxes("x", "y");
      ImPlot::EndPlot();
    }
    ImGui::End();
}

int main() {
  std::cout << "Hello problem 3.1" << std::endl;
  Window window{"wow", 800, 600};

  window.render(fn, plot);

}
