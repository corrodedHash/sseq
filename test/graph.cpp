#include "graph.hpp"
#include "catch.hpp"
#include <iostream>

TEST_CASE("I guess")
{
  auto test = createSquareSequenceGraph<NumberGraph>(30);
  auto x = has_path(test);
  REQUIRE(x);
  REQUIRE(x->size() == 30);
  for (decltype(x->size()) i = 0; i < x->size() - 1; ++i) {
    REQUIRE(is_square_num(static_cast<unsigned long>((*x)[i] + (*x)[i + 1] + 2)));
  }
}
