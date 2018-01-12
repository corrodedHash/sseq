#include <iostream>
#include <cmath>
#include "graph.hpp"
#include "util.hpp"

int main(int argc, char** args)
{
  (void)argc;
  (void)args;
  graph test;
  for (int i = 0; i < 150; ++i) {
    test.nodes.emplace_back();
    for (int j = 0; j < i; ++j) {
      if (is_square_num(i + j + 2)) {
        test.add_bi_edge(i, j);
      }
    }
    if (auto x = test.has_path(); x) {
      std::cout << i + 1 << ":  ";
      for (auto j : x->_vec) {
        std::cout << j + 1 << " ";
      }
      std::cout << "\n";
    }
  }
  return 0;
}
