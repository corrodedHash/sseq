#pragma once
#include <vector>
#include "setvec.hpp"
struct graphnode {
  std::vector<int> neighbors = std::vector<int>(5);
};

struct graph {
  std::vector<graphnode> nodes;
  std::optional<setvec> has_path();
  void add_bi_edge(int i, int j)
  {
    nodes[static_cast<setvec::size_type>(i)].neighbors.push_back(j);
    nodes[static_cast<setvec::size_type>(j)].neighbors.push_back(i);
  }
};
