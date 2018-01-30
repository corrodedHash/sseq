#include "graph.hpp"
#include <boost/graph/graphviz.hpp>
#include <boost/program_options.hpp>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

static void print_graph(unsigned int size)
{
  auto test = createSquareSequenceGraph<NumberGraph>(static_cast<unsigned int>(size));
  auto printer = [](std::ostream& out, const auto& v) {
    out << "[label=\"" << v + 1 << "\"]";
  };
  boost::write_graphviz(std::cout, test, printer);
}

static void iterate_graph(unsigned int start, unsigned int end, bool all)
{
  auto test = createSquareSequenceGraph<NumberGraph>(start);
  for (unsigned int i = start; i != end; ++i) {
    HamiltonPathFinder<NumberGraph> finder(test);

    unsigned path_count = 0;
    auto a = finder.next();
    std::cout << boost::num_vertices(test) << "\n";
    while (a) {
      ++path_count;
      std::cout << " ";
      for (auto x : *a) {
        std::cout << x + 1 << " ";
      }
      std::cout << "\n";
      if (all) {
        a = finder.next();
      } else {
        a = std::nullopt;
      }
    }
    if (all) {
      std::cout
          << "Found paths: " << path_count << "\n";
    }
    appendSquareSequenceGraph(test);
  }
}
int main(int argc, char** args)
{
  namespace po = boost::program_options;
  unsigned int start, end;
  po::options_description desc("Allowed options");
  desc.add_options()("start", po::value<unsigned int>(&start)->default_value(1), "value to start searching at")("end", po::value<unsigned int>(&end)->default_value(0), "stop building sequences at this value")("print", "only print graph")("help", "produce help message")("all", "enumerate all paths");

  po::variables_map vm;
  po::store(po::command_line_parser(argc, args).options(desc).run(), vm);
  po::notify(vm);

  if (vm.count("help")) {
    std::cout << desc << "\n";
    return 0;
  } else if (vm.count("print")) {
    print_graph(start);
  } else {
    iterate_graph(start, end, vm.count("all") > 0);
  }
  return 0;
}
