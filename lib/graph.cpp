#include "graph.hpp"
#include <algorithm>
#include <cryptominisat5/cryptominisat.h>
#include <iostream>

std::optional<std::vector<int>> graph::has_path()
{
  std::vector<int> visited;
  visited.emplace_back(0);
  while (visited.size() < nodes.size()) {
    auto& choices = nodes[static_cast<std::vector<int>::size_type>(visited.back())].neighbors;
    auto next_id_it = std::find_if(std::begin(choices), std::end(choices), [&](int x) { return std::find(std::begin(visited), std::end(visited), x) == std::end(visited); });
    if (next_id_it != std::end(choices)) {
      visited.emplace_back(*next_id_it);
    } else {
      while (true) {
        auto faulty_id = visited.back();
        visited.pop_back();

        if (visited.empty()) {
          if (static_cast<std::vector<int>::size_type>(faulty_id) + 1 >= nodes.size()) {
            return std::nullopt;
          }
          visited.emplace_back(faulty_id + 1);
          break;
        }
        auto& new_choices = nodes[static_cast<std::vector<int>::size_type>(visited.back())].neighbors;
        auto new_next_id_it = std::find_if(std::begin(new_choices), std::end(new_choices), [&](int x) { return (std::find(std::begin(visited), std::end(visited), x) == std::end(visited)) && (x > faulty_id); });
        if (new_next_id_it != std::end(new_choices)) {
          visited.emplace_back(*new_next_id_it);
          break;
        }
      }
    }
  }
  return visited;
}
