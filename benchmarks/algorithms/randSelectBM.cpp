#include <iostream>
#include <numeric>
#include <bits/stdc++.h> 
#include <benchmark/benchmark.h>
#include "orderStatistic.h"

static void BM_randomSelect(benchmark::State& state) 
{
    std::vector<int> v (state.range(0));
    std::iota(v.begin(), v.end(), 0);
    std::random_shuffle(v.begin(), v.end());

    for (auto _ : state)
    {
        //current function under benchmarking
        benchmark::DoNotOptimize(orderStatistics::randSelect(v, 0, v.size()-1, 5));
    }

    state.SetComplexityN(state.range(0));
}

BENCHMARK(BM_randomSelect)->RangeMultiplier(2)->Range(1<<3, 1<<20)->Complexity();

BENCHMARK_MAIN();
