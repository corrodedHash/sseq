#pragma once
#include "graph_util.hpp"
#include <boost/graph/adjacency_list.hpp>
#include <optional>
#include <sstream>
#include <string>
#include <vector>

using NumberGraph =
    boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS>;

template <typename T> class HamiltonPathFinder {
public:
  HamiltonPathFinder(const T& graph_);

  std::optional<std::vector<typename boost::graph_traits<T>::vertex_descriptor>>
  next();

  class iterator;
  friend class iterator;
  iterator begin();
  iterator end();

private:
  const T& graph;
  std::vector<std::pair<typename boost::graph_traits<T>::adjacency_iterator,
                        typename boost::graph_traits<T>::adjacency_iterator>>
      iterator_stack;
  std::vector<typename boost::graph_traits<T>::vertex_descriptor> visited;
  typename boost::graph_traits<T>::vertex_iterator root_it;
  typename boost::graph_traits<T>::vertex_iterator root_end;
};

template <typename T> class HamiltonPathFinder<T>::iterator {
public:
  enum class CompletionStatus { finished, running };
  iterator(HamiltonPathFinder& hpf_, CompletionStatus finished_);
  iterator operator++();
  iterator operator++(int);
  const std::vector<typename boost::graph_traits<T>::vertex_descriptor>&
  operator*();
  const std::vector<typename boost::graph_traits<T>::vertex_descriptor>*
  operator->();
  bool operator==(const iterator& rhs);
  bool operator!=(const iterator& rhs);

private:
  HamiltonPathFinder& hpf;
  bool finished;
};

#include "hpf.tpp"
#include "hpf_iterator.tpp"
