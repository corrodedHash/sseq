#include "graph.hpp"
#include <cmath>
#include <iostream>

int main(int argc, char** args)
{
  (void)argc;
  (void)args;
  NumberGraph test;
  for (unsigned int i = 0; i < 150; ++i) {
    appendSquareSequenceGraph(i, test);
    auto a = has_path(test);
    if (a) {
      std::cout << i + 1 << "\n\t";
      for (auto x : *a) {
        std::cout << x + 1 << " ";
      }
      std::cout << "\n";
    } else {
      std::cout << "-" << i + 1 << "\n";
    }
    std::cout << "\n";
  }
  return 0;
}
