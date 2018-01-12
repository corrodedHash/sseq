#include "graph.hpp"
#include "util.hpp"
#include <benchmark/benchmark.h>

static void BM_Whole(benchmark::State& state)
{
  for (auto _ : state) {
    graph test;
    for (int i = 0; i < 30; ++i) {
      test.nodes.emplace_back();
      for (int j = 0; j < i; ++j) {
        if (is_square_num(i + j + 2)) {
          test.add_bi_edge(i, j);
        }
      }
    }
    auto x = test.has_path();
  }
}
static void BM_GraphGen(benchmark::State& state)
{
  for (auto _ : state) {
    graph test;
    for (int i = 0; i < 30; ++i) {
      test.nodes.emplace_back();
      for (int j = 0; j < i; ++j) {
        if (is_square_num(i + j + 2)) {
          test.add_bi_edge(i, j);
        }
      }
    }
    auto x = test.has_path();
  }
}
static void BM_PathFind(benchmark::State& state)
{
  graph test;
  for (int i = 0; i < 30; ++i) {
    test.nodes.emplace_back();
    for (int j = 0; j < i; ++j) {
      if (is_square_num(i + j + 2)) {
        test.add_bi_edge(i, j);
      }
    }
  }
  for (auto _ : state) {
    auto x = test.has_path();
  }
}

BENCHMARK(BM_Whole);
BENCHMARK(BM_GraphGen);
BENCHMARK(BM_PathFind);
