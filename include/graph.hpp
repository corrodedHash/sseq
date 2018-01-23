#pragma once
#include <boost/graph/adjacency_list.hpp>
#include <optional>
#include <sstream>
#include <string>
#include <vector>

using NumberGraph = boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, boost::property<boost::vertex_index_t, unsigned>>;

NumberGraph createSquareSequenceGraph(unsigned until);
void appendSquareSequenceGraph(unsigned new_index, NumberGraph& g);
std::optional<std::vector<boost::graph_traits<NumberGraph>::vertex_descriptor>> has_path(const NumberGraph& g);

inline bool is_square_num(unsigned long value)
{
  unsigned int root = static_cast<unsigned int>(std::sqrt(value));
  return (root * root == value);
}
