#include "graph.hpp"
#include "util.hpp"
#include <cmath>
#include <iostream>

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
    bool a = static_cast<bool>(test.has_path());
    if (a) {
      std::cout << i + 1 << " ";
    } else {
      std::cout << "-" << i + 1 << " ";
    }
    std::cout << "\n";
  }
  return 0;
}
