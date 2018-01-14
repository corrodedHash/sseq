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
    /*
       if (auto x = test.has_path(); x) {
      std::cout << i + 1 << ":  ";
      for (auto j : x->_vec) {
        std::cout << j + 1 << " ";
      }
      std::cout << "\n";
    }
  */
    bool a = test.has_path_standard() ? true : false;
    bool b = test.has_path_cms();
    if (a) {
      std::cout << i + 1 << " ";
    } else {
      std::cout << "-" << i + 1 << " ";
    }
    if (b) {
      std::cout << i + 1 << "\n";
    } else {
      std::cout << "-" << i + 1 << "\n";
    }
  }
  return 0;
}
