#include "graph.hpp"
#include "catch.hpp"
#include "util.hpp"
#include <iostream>

TEST_CASE("I guess")
{
  graph test;
  for (int i = 0; i < 15; ++i) {
    test.nodes.emplace_back();
    for (int j = 0; j < i; ++j) {
      if (is_square_num(i + j + 2)) {
        test.add_bi_edge(i, j);
      }
    }
  }
  auto x = test.has_path();
  REQUIRE(x);
  for (decltype(x->size()) i = 0; i < x->size() - 1; ++i) {
    REQUIRE(is_square_num((*x)[i] + (*x)[i + 1] + 2));
  }
}
