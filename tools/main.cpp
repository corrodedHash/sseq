#include "graph.hpp"
#include <boost/graph/graphviz.hpp>
#include <boost/program_options.hpp>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

void print_graph(unsigned int size)
{
  NumberGraph test = createSquareSequenceGraph(static_cast<unsigned int>(size));
  auto printer = [](std::ostream& out, const auto& v) {
    out << "[label=\"" << v + 1 << "\"]";
  };
  boost::write_graphviz(std::cout, test, printer);
}

void iterate_graph(unsigned int start, unsigned int end)
{
  NumberGraph test = createSquareSequenceGraph(start);
  for (unsigned int i = start; i != end; ++i) {
    auto a = has_path(test);
    if (a) {
      std::cout << boost::num_vertices(test) << "\n  ";
      for (auto x : *a) {
        std::cout << x + 1 << " ";
      }
      std::cout << "\n";
    } else {
      std::cout << "-" << i + 1 << "\n";
    }
    std::cout << "\n";
    appendSquareSequenceGraph(test);
  }
}
int main(int argc, char** args)
{
  namespace po = boost::program_options;
  unsigned int start, end;
  po::options_description desc("Allowed options");
  desc.add_options()("start", po::value<unsigned int>(&start)->default_value(1), "value to start searching at")("end", po::value<unsigned int>(&end)->default_value(0), "stop building sequences at this value")("print", "only print graph");

  po::variables_map vm;
  po::store(po::command_line_parser(argc, args).options(desc).run(), vm);
  po::notify(vm);

  if (vm.count("print")) {
    print_graph(start);
  } else {
    iterate_graph(start, end);
  }
  return 0;
}
