#include "graph.hpp"
#include "catch.hpp"
#include "util.hpp"

TEST_CASE("I guess")
{
  graph test;
  for (int i = 0; i < 30; ++i) {
    test.nodes.emplace_back();
    for (int j = 0; j < i; ++j) {
      if (is_square_num(i + j + 2)) {
        test.add_bi_edge(i, j);
      }
    }
  }
  auto x = test.has_path();
  REQUIRE(x);
  for (decltype(x->_vec.size()) i = 0; i < x->_vec.size() - 1; ++i) {
    REQUIRE(is_square_num(x->_vec[i] + x->_vec[i + 1] + 2));
  }
}
