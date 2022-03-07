#include <iostream>
#include <numeric>
#include <bits/stdc++.h> 
#include <benchmark/benchmark.h>
#include "sorting.h"

static void BM_bubble_sort(benchmark::State& state) 
{
    std::vector<int> v (state.range(0));
    std::iota(v.begin(), v.end(), 2);
    std::reverse(v.begin(), v.end());

    for (auto _ : state)
    {
        //current function under benchmarking
        benchmark::DoNotOptimize(sorting::bubbleSort(v));
    }
    state.SetComplexityN(state.range(0));
}

BENCHMARK(BM_bubble_sort)->RangeMultiplier(2)->Range(1<<5, 1<<20)->Complexity(benchmark::oN);

BENCHMARK_MAIN();
