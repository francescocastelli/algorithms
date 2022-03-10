#include <iostream>
#include <numeric>
#include <bits/stdc++.h> 
#include <benchmark/benchmark.h>
#include "sorting.h"

static void BM_mergeSort_avg_case(benchmark::State& state) 
{
    std::vector<int> v (state.range(0));
    std::iota(v.begin(), v.end(), 2);

    for (auto _ : state)
    {
        benchmark::DoNotOptimize(sorting::mergeSort(v));
    }
    state.SetComplexityN(state.range(0));

}

BENCHMARK(BM_mergeSort_avg_case)->RangeMultiplier(2)->Range(1<<2, 1<<20)
                                ->Complexity(benchmark::oNLogN);

BENCHMARK_MAIN();
