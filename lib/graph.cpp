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
    boost::add_vertex(result);
    for (unsigned j = 0; j < i; ++j) {
      if (is_square_num(j + i + 2)) {
        boost::add_edge(i, j, result);
      }
    }
  }
  return result;
}

std::optional<std::vector<boost::graph_traits<NumberGraph>::vertex_descriptor>> has_path(const NumberGraph& g)
{
  std::vector<std::pair<boost::graph_traits<NumberGraph>::adjacency_iterator, boost::graph_traits<NumberGraph>::adjacency_iterator>> iterator_stack;
  std::vector<boost::graph_traits<NumberGraph>::vertex_descriptor> visited;

  visited.reserve(boost::num_vertices(g));
  iterator_stack.reserve(boost::num_vertices(g));
  for (auto[root, it_end] = boost::vertices(g); root != it_end; ++root) {
    visited.push_back(*root);
    iterator_stack.push_back(boost::adjacent_vertices(visited.back(), g));
    while (!iterator_stack.empty()) {
      while (iterator_stack.back().first != iterator_stack.back().second) {
        if (std::find(std::begin(visited), std::end(visited), *iterator_stack.back().first) == std::end(visited)) {
          visited.push_back(*iterator_stack.back().first);
          ++iterator_stack.back().first;
          iterator_stack.push_back(boost::adjacent_vertices(visited.back(), g));
          break;
        }
        ++iterator_stack.back().first;
      }
      if (iterator_stack.back().first == iterator_stack.back().second) {
        visited.pop_back();
        iterator_stack.pop_back();
      } else if (visited.size() == boost::num_vertices(g)) {
        return visited;
      }
    }
  }
  return std::nullopt;
}
