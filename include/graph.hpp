#pragma once
#include <cryptominisat5/cryptominisat.h>
#include <optional>
#include <sstream>
#include <string>
#include <vector>

struct graphnode {
  std::vector<int> neighbors;
};

struct graph {
  std::vector<graphnode> nodes;
  std::optional<std::vector<int>> has_path();
  void add_bi_edge(int i, int j)
  {
    nodes[static_cast<std::vector<int>::size_type>(i)].neighbors.push_back(j);
    nodes[static_cast<std::vector<int>::size_type>(j)].neighbors.push_back(i);
  }

  std::string dump()
  {
    std::stringstream ss;
    for (std::vector<int>::size_type i = 0; i < nodes.size(); ++i) {
      ss << i + 1 << "\n  ";
      for (auto j : nodes[i].neighbors) {
        ss << j + 1 << " ";
      }
      ss << "\n";
    }
    return ss.str();
  }
};
