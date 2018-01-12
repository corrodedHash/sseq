#include "graph.hpp"
#include "util.hpp"
#include <benchmark/benchmark.h>

static void BM_Whole(benchmark::State& state)
{
  for (auto _ : state) {
    graph test;
    for (int i = 0; i < state.range(0); ++i) {
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
    for (int i = 0; i < state.range(0); ++i) {
      test.nodes.emplace_back();
      for (int j = 0; j < i; ++j) {
        if (is_square_num(i + j + 2)) {
          test.add_bi_edge(i, j);
        }
      }
    }
  }
}
static void BM_PathFind(benchmark::State& state)
{
  graph test;
  for (int i = 0; i < state.range(0); ++i) {
    test.nodes.emplace_back();
    for (int j = 0; j < i; ++j) {
      if (is_square_num(i + j + 2)) {
        test.add_bi_edge(i, j);
      }
    }
  }
  for (auto _ : state) {
    benchmark::DoNotOptimize(test.has_path());
  }
  state.SetComplexityN(state.range(0));
}

BENCHMARK(BM_Whole)->RangeMultiplier(2)->Range(1, 32);
BENCHMARK(BM_GraphGen)->RangeMultiplier(2)->Range(1, 32);
BENCHMARK(BM_PathFind)->RangeMultiplier(2)->Range(1, 32)->Complexity();
