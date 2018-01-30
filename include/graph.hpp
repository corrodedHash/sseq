#pragma once
#include <boost/graph/adjacency_list.hpp>
#include <optional>
#include <sstream>
#include <string>
#include <vector>

using NumberGraph = boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS>;

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

template <typename T>
class HamiltonPathFinder {
  public:
  HamiltonPathFinder(const T& graph_)
      : graph(graph_)
  {
    visited.reserve(boost::num_vertices(graph));
    iterator_stack.reserve(boost::num_vertices(graph));
    auto it_pair = boost::vertices(graph);
    root_it = it_pair.first;
    root_end = it_pair.second;
  }

  std::optional<std::vector<typename boost::graph_traits<T>::vertex_descriptor>> next()
  {
    while (root_it != root_end) {
      visited.push_back(*root_it);
      iterator_stack.push_back(boost::adjacent_vertices(visited.back(), graph));
      while (!iterator_stack.empty()) {
        while (iterator_stack.back().first != iterator_stack.back().second) {
          if (std::find(std::begin(visited), std::end(visited), *iterator_stack.back().first) == std::end(visited)) {
            visited.push_back(*iterator_stack.back().first);
            ++iterator_stack.back().first;
            iterator_stack.push_back(boost::adjacent_vertices(visited.back(), graph));

            break;
          }
          ++iterator_stack.back().first;
        }
        if (iterator_stack.back().first == iterator_stack.back().second) {
          visited.pop_back();
          iterator_stack.pop_back();
        } else if (visited.size() == boost::num_vertices(graph)) {
          return visited;
        }
      }
      ++root_it;
    }
    return std::nullopt;
  }

  private:
  const T& graph;
  std::vector<std::pair<typename boost::graph_traits<T>::adjacency_iterator, typename boost::graph_traits<T>::adjacency_iterator>> iterator_stack;
  std::vector<typename boost::graph_traits<T>::vertex_descriptor> visited;
  typename boost::graph_traits<T>::vertex_iterator root_it;
  typename boost::graph_traits<T>::vertex_iterator root_end;
};
