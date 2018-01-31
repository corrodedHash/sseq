#include "helper.hpp"
#include <boost/program_options.hpp>
#include <iostream>

int main(int argc, char** args)
{
  namespace po = boost::program_options;
  unsigned int start, end;
  po::options_description desc("Allowed options");
  desc.add_options()("start", po::value<unsigned int>(&start)->default_value(1), "value to start searching at")("end", po::value<unsigned int>(&end)->default_value(0), "stop building sequences at this value")("print", "only print graph")("help", "produce help message")("all", "enumerate all paths")("count", "count paths");

  po::variables_map vm;
  po::store(po::command_line_parser(argc, args).options(desc).run(), vm);
  po::notify(vm);

  if (vm.count("help") != 0) {
    std::cout << desc << "\n";
    return 0;
  }
  if (vm.count("print") != 0) {
    print_graph(start);
  } else if (vm.count("all") != 0) {
    exhaust_graph(start, end);
  } else if (vm.count("count") != 0) {
    count_graph(start, end);
  } else {
    iterate_graph(start, end);
  }
  return 0;
}
