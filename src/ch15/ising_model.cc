#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "implot.h"
#include <cstdlib>
#define GLAD_GL_IMPLEMENTATION
#include <iostream>
#include <cmath>
#include <algorithm>
#include <random>
#include "core/window.hh"


constexpr int width = 64;
float data[width][width] = {};

auto fn() -> void {
  for (auto& row : data) {
    for (auto& col : row) {
      double r = (double)std::rand() / RAND_MAX;
      if (r > 0.5) {
        col = 1.0f;
      } else {
        col = -1.0f;
      }
    }
  }
}

auto plot() -> void {
  ImGuiIO& io = ImGui::GetIO();
  ImGui::Begin("Simulation");
  ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
  static ImPlotAxisFlags axes_flags = ImPlotAxisFlags_Lock | ImPlotAxisFlags_NoGridLines | ImPlotAxisFlags_NoTickMarks | ImPlotAxisFlags_NoTickLabels;
  static float scale_min = -1.0f;
  static float scale_max =  1.0f;
  ImPlot::PushColormap("Greys");
  if (ImPlot::BeginPlot("##Heatmap1",ImVec2(-1,-1),ImPlotFlags_NoLegend|ImPlotFlags_NoMouseText)) {
      ImPlot::SetupAxes(nullptr, nullptr, ImPlotAxisFlags_NoDecorations, ImPlotAxisFlags_NoDecorations);
      ImPlot::SetupAxisTicks(ImAxis_X1,0 + 1.0/14.0, 1 - 1.0/14.0, 7);
      ImPlot::SetupAxisTicks(ImAxis_Y1,1 - 1.0/14.0, 0 + 1.0/14.0, 7);
      ImPlot::PlotHeatmap("heat",data[0],width,width,scale_min,scale_max,nullptr,ImPlotPoint(0,0),ImPlotPoint(1,1));
      ImPlot::EndPlot();
  }
  ImGui::End();
}

int main() {
  std::cout << "Hello problem 3.1" << std::endl;
  Window window{"wow", 800, 600};
  std::srand(0);

  window.render(fn, plot);

}

