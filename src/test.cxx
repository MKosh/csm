#include <iostream>

#include <matplot/matplot.h>
#include <vector>
#include <set>
#include <chrono>
#include <thread>

int main() {
  using namespace matplot;

  std::cout << "hello" << std::endl;
  std::vector<std::vector<double>> Y = {
    {16,5,9,4,1},{11,3,4,15,10}};
  // plot(Y);
  // show();
  
  auto f = figure(false);
  auto ax = gca();
  auto p = ax->plot(Y);
  p[0]->color("black").line_width(2);
  std::cout << p.size() << std::endl;
  ax->draw();

  for (int i = 0; i < 50; ++i) {
    // std::this_thread::sleep_for(std::chrono::milliseconds(60));
    Y[0][1] += 2;
    p = ax->plot(Y);
    p[0]->color("black").line_width(2);
    ax->draw();
  }

  // std::cin.get();


  return 0;
}
