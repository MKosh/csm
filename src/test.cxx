#include <iostream>

#include <matplot/matplot.h>
#include <vector>
#include <set>

int main() {
  using namespace matplot;

  std::cout << "hello" << std::endl;
  std::set<std::vector<double>> Y = {
    {16,5,9,4,1},{11,3,4,15,10}};
  plot(Y);
  wait();

  return 0;
}
