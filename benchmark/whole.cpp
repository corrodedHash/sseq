#include "graph.hpp"
#include <benchmark/benchmark.h>

static void BM_Whole(benchmark::State& state)
{
  for (auto _ : state) {
    auto x = has_path(createSquareSequenceGraph(static_cast<unsigned int>(state.range(0))));
  }
}
static void BM_GraphGen(benchmark::State& state)
{
  for (auto _ : state) {
    createSquareSequenceGraph(static_cast<unsigned int>(state.range(0)));
  }
}
static void BM_PathFindStandard(benchmark::State& state)
{
  auto test = createSquareSequenceGraph(static_cast<unsigned int>(state.range(0)));
  for (auto _ : state) {
    benchmark::DoNotOptimize(has_path(test));
  }
}

BENCHMARK(BM_Whole)->RangeMultiplier(2)->Range(1, 32);
BENCHMARK(BM_GraphGen)->RangeMultiplier(2)->Range(1, 32);
BENCHMARK(BM_PathFindStandard)->RangeMultiplier(2)->Range(1, 32);
