#include <iostream>
#include <numeric>
#include <bits/stdc++.h> 
#include <benchmark/benchmark.h>
#include "orderStatistic.h"

static void BM_minMax(benchmark::State& state) 
{
    std::vector<int> v (state.range(0));
    std::iota(v.begin(), v.end(), 0);
    std::random_shuffle(v.begin(), v.end());
    int min, max;

    for (auto _ : state)
    {
        //current function under benchmarking
        benchmark::DoNotOptimize(orderStatistics::minmax(v, min, max));
    }

    state.SetComplexityN(state.range(0));
}

BENCHMARK(BM_minMax)->RangeMultiplier(2)->Range(1<<2, 1<<16)->Complexity();
BENCHMARK_MAIN();
