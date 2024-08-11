#include <cstdint>
#include <matplot/matplot.h>

#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <thread>

const float m_0 = 1000.f;
const int32_t n_agents = 100;

int main (int argc, char *argv[]) {
  using namespace matplot;

  std::vector<float> m(n_agents, m_0);

  std::mt19937 mt{ std::random_device{}() };
  std::uniform_real_distribution<float> random_epsilon;
  std::uniform_int_distribution<> random_agent{0, n_agents - 1};

  auto f = figure(false);
  auto ax = gca();
  auto p = ax->plot(m);
  // show();

  int32_t agent_i = -1;
  int32_t agent_j = -1;
  float m_i = -1.f;
  float m_j = -1.f;
  float epsilon = -1.f;
  // while (std::cin.get() != '\n') {
  int32_t iters = 10000;
  for (int32_t i = 0; i < iters; ++i) {
    agent_i = random_agent(mt);
    agent_j = random_agent(mt);
    m_i = m.at(agent_i);
    m_j = m.at(agent_j);
    epsilon = random_epsilon(mt);

    m.at(agent_i) = epsilon * (m_i + m_j);
    m.at(agent_j) = (1 - epsilon) * (m_i + m_j);

    if (i % 10 == 0) {
      p = ax->plot(m);
      ax->draw();
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }

  return 0;
}
