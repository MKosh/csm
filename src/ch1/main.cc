#define GLAD_GL_IMPLEMENTATION
#define GLFW_INCLUDE_NONE
#include "distribution_of_money.h"

const uint32_t g_width = 800;
const uint32_t g_height= 600;

int main(int argc, char* argv[]) {
  DistributionOfMoney simulation;
  simulation.InitWindow(g_width, g_height);
  simulation.Run();
  simulation.Cleanup();

  return 0;
}
