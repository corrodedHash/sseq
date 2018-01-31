#pragma once
#include <cmath>
#include <boost/graph/adjacency_list.hpp>

inline bool is_square_num(unsigned long value)
{
  unsigned int root = static_cast<unsigned int>(std::sqrt(value));
  return (root * root == value);
}

template <typename T>
void appendSquareSequenceGraph(T& g)
{
  auto new_index = boost::num_vertices(g);
  boost::add_vertex(g);
  for (unsigned j = 0; j < new_index; ++j) {
    if (is_square_num(j + new_index + 2)) {
      boost::add_edge(new_index, j, g);
    }
  }
}

template <typename T>
T createSquareSequenceGraph(unsigned until)
{
  T result;
  for (unsigned i = 0; i < until; ++i) {
    appendSquareSequenceGraph<T>(result);
  }
  return result;
}
