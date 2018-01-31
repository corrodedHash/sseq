#include "helper.hpp"
#include "graph.hpp"
#include <boost/graph/graphviz.hpp>
#include <functional>
#include <iostream>
#include <vector>

void print_graph(unsigned int size) {
  auto test =
      createSquareSequenceGraph<NumberGraph>(static_cast<unsigned int>(size));
  auto printer = [](std::ostream& out, const auto& v) {
    out << "[label=\"" << v + 1 << "\"]";
  };
  boost::write_graphviz(std::cout, test, printer);
}

static void increment_graph(
    unsigned int start, unsigned int end,
    const std::function<void(HamiltonPathFinder<NumberGraph>&)>& worker) {
  auto test = createSquareSequenceGraph<NumberGraph>(start);
  for (unsigned int i = start; i != end; ++i) {
    HamiltonPathFinder<NumberGraph> finder(test);
    std::cout << boost::num_vertices(test) << "\n";
    worker(finder);
    appendSquareSequenceGraph(test);
  }
}

static void iterate_graph_intern(HamiltonPathFinder<NumberGraph>& finder) {
  auto path = finder.next();
  if (!path) {
    std::cout << "  -\n";
  } else {
    std::cout << "  ";
    for (auto& vertex : *path) {
      std::cout << vertex + 1 << " ";
    }
    std::cout << "\n";
  }
}

static void exhaust_graph_intern(HamiltonPathFinder<NumberGraph>& finder) {
  for (auto& path : finder) {
    std::cout << "  ";
    for (auto& vertex : path) {
      std::cout << vertex + 1 << " ";
    }
    std::cout << "\n";
  }
}

static void count_graph_intern(HamiltonPathFinder<NumberGraph>& finder) {
  unsigned int path_count = 0;
  for (auto& a : finder) {
    (void)a;
    ++path_count;
  }
  std::cout << " Found paths: " << path_count << '\n';
}

void iterate_graph(unsigned int start, unsigned int end) {
  increment_graph(start, end, iterate_graph_intern);
}
void exhaust_graph(unsigned int start, unsigned int end) {
  increment_graph(start, end, exhaust_graph_intern);
}
void count_graph(unsigned int start, unsigned int end) {
  increment_graph(start, end, count_graph_intern);
}
