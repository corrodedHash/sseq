#include "graph.hpp"
#include <algorithm>
#include <iostream>

std::optional<setvec> graph::has_path()
{
  setvec visited;
  visited.push(0);
  while (visited.size() < nodes.size()) {
    auto choices = nodes[static_cast<setvec::size_type>(visited.back())].neighbors;
    auto next_id_it = std::find_if(std::begin(choices), std::end(choices), [&](int x) { return !visited.contains(x); });
    if (next_id_it != std::end(choices)) {
      visited.push(*next_id_it);
    }
    while (next_id_it == std::end(choices)) {
      auto faulty_id = visited.pop();

      if (visited.empty()) {
        if (static_cast<setvec::size_type>(faulty_id + 1) >= nodes.size()) {
          return std::nullopt;
        }
        visited.push(faulty_id + 1);
        break;
      } else {
        choices = nodes[static_cast<setvec::size_type>(visited.back())].neighbors;
        next_id_it = std::find_if(std::begin(choices), std::end(choices), [&](int x) { return (!visited.contains(x)) && (x > faulty_id); });
        if (next_id_it != std::end(choices)) {
          visited.push(*next_id_it);
        }
      }
    }
  }
  return visited;
}
