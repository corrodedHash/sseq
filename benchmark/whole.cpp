#include "graph.hpp"
#include <benchmark/benchmark.h>

static void BM_Whole(benchmark::State& state) {
  for (auto _ : state) {
    (void)_;
    auto test = createSquareSequenceGraph<NumberGraph>(
        static_cast<unsigned int>(state.range(0)));
    HamiltonPathFinder<NumberGraph> finder(test);
    auto x = finder.next();
  }
}
static void BM_GraphGen(benchmark::State& state) {
  for (auto _ : state) {
    (void)_;
    createSquareSequenceGraph<NumberGraph>(
        static_cast<unsigned int>(state.range(0)));
  }
}
static void BM_PathFindStandard(benchmark::State& state) {
  auto test = createSquareSequenceGraph<NumberGraph>(
      static_cast<unsigned int>(state.range(0)));
  for (auto _ : state) {
    (void)_;
    HamiltonPathFinder<NumberGraph> finder(test);
    finder.next();
  }
}
static void BM_PathFindExhaustive(benchmark::State& state) {
  auto test = createSquareSequenceGraph<NumberGraph>(
      static_cast<unsigned int>(state.range(0)));
  for (auto _ : state) {
    (void)_;
    HamiltonPathFinder<NumberGraph> finder(test);
    for (const auto& x : finder) {
      (void)x;
    }
  }
}

BENCHMARK(BM_Whole)->RangeMultiplier(2)->Range(1, 32);
BENCHMARK(BM_GraphGen)->RangeMultiplier(2)->Range(1, 32);
BENCHMARK(BM_PathFindStandard)->RangeMultiplier(2)->Range(1, 32);
BENCHMARK(BM_PathFindExhaustive)->RangeMultiplier(2)->Range(1, 32);
