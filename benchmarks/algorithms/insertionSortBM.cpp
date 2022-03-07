#include <iostream>
#include <numeric>
#include <bits/stdc++.h> 
#include <benchmark/benchmark.h>
#include "sorting.h"

static void BM_InsertionSort(benchmark::State& state) 
{
    std::vector<int> v (state.range(0));
    std::iota(v.begin(), v.end(), 2);
    //worst case analysis for insertion sort -> reversed ordert input
    std::reverse(v.begin(), v.end());

    for (auto _ : state)
    {
        //current function under benchmarking
        benchmark::DoNotOptimize(sorting::insertionSort(v));
    }
    state.SetComplexityN(state.range(0));
}

BENCHMARK(BM_InsertionSort)->RangeMultiplier(2)->Range(1<<2, 1<<16)->Complexity();
BENCHMARK_MAIN();
