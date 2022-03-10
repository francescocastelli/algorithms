#include <iostream>
#include <numeric>
#include <bits/stdc++.h> 
#include <benchmark/benchmark.h>
#include "sorting.h"

static void BM_CountingSort(benchmark::State& state) 
{
    std::vector<int> v (state.range(0));
    std::iota(v.begin(), v.end(), 0);
    std::random_shuffle(v.begin(), v.end());

    for (auto _ : state)
    {
        //current function under benchmarking
        benchmark::DoNotOptimize(sorting::countingSort(v));
    }

    state.SetComplexityN(state.range(0));
}

BENCHMARK(BM_CountingSort)->RangeMultiplier(2)->Range(1<<2, 1<<16)
                          ->Complexity(benchmark::oN);

BENCHMARK_MAIN();
