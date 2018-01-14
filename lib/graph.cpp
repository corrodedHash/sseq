#include "graph.hpp"
#include <algorithm>
#include <cryptominisat5/cryptominisat.h>
#include <iostream>

std::optional<std::vector<int>> graph::has_path_standard()
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

CMSat::SATSolver graph::create_solver()
{
  CMSat::SATSolver solver;
  std::vector<CMSat::Lit> clause;
  solver.new_vars(nodes.size() * nodes.size());
  // Every node has to appear in the path
  for (int node = 0; node < nodes.size(); ++node) {
    for (int place = 0; place < nodes.size(); ++place) {
      clause.emplace_back(CMSat::Lit(place * nodes.size() + node, false));
    }
    solver.add_clause(clause);
    clause.clear();
  }
  // In every place of the path a node has to appear
  for (int place = 0; place < nodes.size(); ++place) {
    for (int node = 0; node < nodes.size(); ++node) {
      clause.emplace_back(CMSat::Lit(place * nodes.size() + node, false));
    }
    solver.add_clause(clause);
    clause.clear();
  }
  // No node appears twice in the path
  for (int node = 0; node < nodes.size(); ++node) {
    for (int place1 = 0; place1 < nodes.size(); ++place1) {
      for (int place2 = place1 + 1; place2 < nodes.size(); ++place2) {
        clause.emplace_back(CMSat::Lit(place1 * nodes.size() + node, true));
        clause.emplace_back(CMSat::Lit(place2 * nodes.size() + node, true));
        solver.add_clause(clause);
        clause.clear();
      }
    }
  }
  // No two nodes occupy the same place in the path
  for (int place = 0; place < nodes.size(); ++place) {
    for (int node1 = 0; node1 < nodes.size(); ++node1) {
      for (int node2 = node1 + 1; node2 < nodes.size(); ++node2) {
        clause.emplace_back(CMSat::Lit(place * nodes.size() + node1, true));
        clause.emplace_back(CMSat::Lit(place * nodes.size() + node2, true));
        solver.add_clause(clause);
        clause.clear();
      }
    }
  }
  // Nonadjacent nodes cannot be adjacent in the path
  for (int node1 = 0; node1 < nodes.size(); ++node1) {
    for (int place = 0; place < nodes.size() - 1; ++place) {
      for (int node2 = 0; node2 < nodes.size(); ++node2) {
        if (std::find(nodes[node1].neighbors.begin(), nodes[node1].neighbors.end(), node2) == std::end(nodes[node1].neighbors)) {
          clause.emplace_back(CMSat::Lit(place * nodes.size() + node1, true));
          clause.emplace_back(CMSat::Lit((place + 1) * nodes.size() + node2, true));
          solver.add_clause(clause);
          clause.clear();
        }
      }
    }
  }
  return solver;
}

bool graph::has_path_cms()
{
  auto x = create_solver().solve();
  return x == CMSat::l_True;
}

bool graph::has_path()
{
  return has_path_cms();
}
