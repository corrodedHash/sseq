#include "graph.hpp"
#include <algorithm>
#include <iostream>

std::optional<setvec> graph::has_path()
{
  setvec visited;
  visited.push(0);
  while (visited.size() < nodes.size()) {
    auto& choices = nodes[static_cast<setvec::size_type>(visited.back())].neighbors;
    auto next_id_it = std::find_if(std::begin(choices), std::end(choices), [&](int x) { return !visited.contains(x); });
    if (next_id_it != std::end(choices)) {
      visited.push(*next_id_it);
    }
    while (true) {
      auto faulty_id = visited.pop();

      if (visited.empty()) {
        if (static_cast<setvec::size_type>(faulty_id) + 1 >= nodes.size()) {
          return std::nullopt;
        }
        visited.push(faulty_id + 1);
        break;
      }
      auto& new_choices = nodes[static_cast<setvec::size_type>(visited.back())].neighbors;
      auto new_next_id_it = std::find_if(std::begin(new_choices), std::end(new_choices), [&](int x) { return (!visited.contains(x)) && (x > faulty_id); });
      if (new_next_id_it != std::end(new_choices)) {
        visited.push(*new_next_id_it);
        break;
      }
    }
  }
  return visited;
}
