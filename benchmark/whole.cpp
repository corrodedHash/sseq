#include "graph.hpp"
#include "util.hpp"
#include <benchmark/benchmark.h>

static graph createGraph(int size)
{
  graph test;
  for (int i = 0; i < size; ++i) {
    test.nodes.emplace_back();
    for (int j = 0; j < i; ++j) {
      if (is_square_num(i + j + 2)) {
        test.add_bi_edge(i, j);
      }
    }
  }
  return test;
}
static void BM_Whole(benchmark::State& state)
{
  for (auto _ : state) {
    auto x = createGraph(state.range(0)).has_path();
  }
}
static void BM_GraphGen(benchmark::State& state)
{
  for (auto _ : state) {
    createGraph(state.range(0));
  }
}
static void BM_PathFindStandard(benchmark::State& state)
{
  auto test = createGraph(state.range(0));
  for (auto _ : state) {
    benchmark::DoNotOptimize(test.has_path_standard());
  }
}
static void BM_PathFindCMS(benchmark::State& state)
{
  auto test = createGraph(state.range(0));
  for (auto _ : state) {
    benchmark::DoNotOptimize(test.has_path_cms());
  }
}

static void BM_CreateSolver(benchmark::State& state)
{
  auto test = createGraph(state.range(0));
  for (auto _ : state) {
    benchmark::DoNotOptimize(test.create_solver());
  }
}

BENCHMARK(BM_Whole)->RangeMultiplier(2)->Range(1, 32);
BENCHMARK(BM_GraphGen)->RangeMultiplier(2)->Range(1, 32);
BENCHMARK(BM_PathFindStandard)->RangeMultiplier(2)->Range(1, 32);
BENCHMARK(BM_PathFindCMS)->RangeMultiplier(2)->Range(1, 32);
BENCHMARK(BM_CreateSolver)->RangeMultiplier(2)->Range(1, 32);
