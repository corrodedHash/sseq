#include <iostream>
#include <cmath>
#include "graph.hpp"

int main(int argc, char** args)
{
  (void)argc;
  (void)args;
  graph test;
  for (int i = 0; i < 50; ++i) {
    test.nodes.emplace_back();
    for (int j = 0; j < i; ++j) {
      int cur = i + 1 + j + 1;
      int root = static_cast<int>(std::sqrt(cur));
      if (root * root == cur) {
        test.add_bi_edge(i, j);
      }
    }
    if (auto x = test.has_path(); x) {
      std::cout << i + 1 << "\n  ";
      for (auto j : x->_vec) {
        std::cout << j + 1 << " ";
      }
      std::cout << "\n";
    }
  }
  return 0;
}
