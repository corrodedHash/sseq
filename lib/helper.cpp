#include "graph.hpp"
#include "helper.hpp"
#include <iostream>
#include <vector>
#include <boost/graph/graphviz.hpp>

void print_graph(unsigned int size)
{
  auto test = createSquareSequenceGraph<NumberGraph>(static_cast<unsigned int>(size));
  auto printer = [](std::ostream& out, const auto& v) {
    out << "[label=\"" << v + 1 << "\"]";
  };
  boost::write_graphviz(std::cout, test, printer);
}

void iterate_graph(unsigned int start, unsigned int end)
{
  auto test = createSquareSequenceGraph<NumberGraph>(start);
  for (unsigned int i = start; i != end; ++i) {
    HamiltonPathFinder<NumberGraph> finder(test);

    auto a = finder.next();
    if (!a) {
      std::cout << "-";
    }
    std::cout << boost::num_vertices(test) << "\n";
    if (a) {
      std::cout << "  ";
      for (auto& x : *a) {
        std::cout << x + 1 << " ";
      }
      std::cout << "\n";
    }
    appendSquareSequenceGraph(test);
  }
}

void exhaust_graph(unsigned int start, unsigned int end)
{
  auto test = createSquareSequenceGraph<NumberGraph>(start);
  for (unsigned int i = start; i != end; ++i) {
    HamiltonPathFinder<NumberGraph> finder(test);
    std::cout << i << "\n";
    for (auto& a : finder) {
      std::cout
          << "  ";
      for (auto& x : a) {
        std::cout << x + 1 << " ";
      }
      std::cout << "\n";
    }
    appendSquareSequenceGraph(test);
  }
}
void count_graph(unsigned int start, unsigned int end)
{
  auto test = createSquareSequenceGraph<NumberGraph>(start);
  for (unsigned int i = start; i != end; ++i) {
    HamiltonPathFinder<NumberGraph> finder(test);
    unsigned int path_count = 0;
    std::cout << i << "\n";
    for (auto& a : finder) {
      (void)a;
      ++path_count;
    }
    std::cout << " Found paths: " << path_count << '\n';
    appendSquareSequenceGraph(test);
  }
}
