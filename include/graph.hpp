#pragma once
#include <boost/graph/adjacency_list.hpp>
#include <optional>
#include <sstream>
#include <string>
#include <vector>

using NumberGraph = boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS>;

NumberGraph createSquareSequenceGraph(unsigned until);
void appendSquareSequenceGraph(NumberGraph& g);

inline bool is_square_num(unsigned long value)
{
  unsigned int root = static_cast<unsigned int>(std::sqrt(value));
  return (root * root == value);
}

template <typename T>
std::optional<std::vector<typename boost::graph_traits<T>::vertex_descriptor>> has_path(const T& g)
{
  std::vector<std::pair<typename boost::graph_traits<T>::adjacency_iterator, typename boost::graph_traits<T>::adjacency_iterator>> iterator_stack;
  std::vector<typename boost::graph_traits<T>::vertex_descriptor> visited;

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
