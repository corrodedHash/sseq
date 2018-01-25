#include "graph.hpp"
#include <boost/program_options.hpp>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char** args)
{
  namespace po = boost::program_options;
  unsigned int start, end;
  po::options_description desc("Allowed options");
  desc.add_options()("start", po::value<unsigned int>(&start)->default_value(1), "value to start searching at")("end", po::value<unsigned int>(&end)->default_value(0), "stop building sequences at this value");

  po::variables_map vm;
  po::store(po::command_line_parser(argc, args).options(desc).run(), vm);
  po::notify(vm);
  NumberGraph test = createSquareSequenceGraph(static_cast<unsigned int>(start));
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
  return 0;
}
