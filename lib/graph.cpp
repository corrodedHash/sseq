#include "graph.hpp"
#include <algorithm>
#include <boost/graph/adjacency_iterator.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_traits.hpp>
#include <iostream>


void appendSquareSequenceGraph(unsigned new_index, NumberGraph& g)
{
  boost::add_vertex(g);
  for (unsigned j = 0; j < new_index; ++j) {
    if (is_square_num(j + new_index + 2)) {
      boost::add_edge(new_index, j, g);
    }
  }
}

NumberGraph createSquareSequenceGraph(unsigned until)
{
  NumberGraph result;
  for (unsigned i = 0; i < until; ++i) {
    appendSquareSequenceGraph(i, result);
  }
  return result;
}

