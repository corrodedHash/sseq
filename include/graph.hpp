#pragma once
#include "setvec.hpp"
#include <sstream>
#include <string>
#include <vector>

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

  std::string dump()
  {
    std::stringstream ss;
    for (int i = 0; i < nodes.size(); ++i) {
      ss << i + 1 << "\n  ";
      for (auto j : nodes[i].neighbors) {
        ss << j + 1 << " ";
      }
      ss << "\n";
    }
    return ss.str();
  }
};
