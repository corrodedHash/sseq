#include "graph.hpp"
#include <benchmark/benchmark.h>

static void BM_Whole(benchmark::State& state)
{
  for (auto _ : state) {
    auto test = createSquareSequenceGraph<NumberGraph>(static_cast<unsigned int>(state.range(0)));
    HamiltonPathFinder<NumberGraph> finder(test);
    auto x = finder.next();
  }
}
static void BM_GraphGen(benchmark::State& state)
{
  for (auto _ : state) {
    createSquareSequenceGraph<NumberGraph>(static_cast<unsigned int>(state.range(0)));
  }
}
static void BM_PathFindStandard(benchmark::State& state)
{
  auto test = createSquareSequenceGraph<NumberGraph>(static_cast<unsigned int>(state.range(0)));
  for (auto _ : state) {
    HamiltonPathFinder<NumberGraph> finder(test);
    benchmark::DoNotOptimize(finder.next());
  }
}

BENCHMARK(BM_Whole)->RangeMultiplier(2)->Range(1, 32);
BENCHMARK(BM_GraphGen)->RangeMultiplier(2)->Range(1, 32);
BENCHMARK(BM_PathFindStandard)->RangeMultiplier(2)->Range(1, 32);
