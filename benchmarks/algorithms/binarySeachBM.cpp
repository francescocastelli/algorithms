#include <iostream>
#include <numeric>
#include <bits/stdc++.h> 
#include <benchmark/benchmark.h>
#include "search.h"

//worst case binary search
static void BM_binary_search_worstCase(benchmark::State& state) 
{
    std::vector<int> v (state.range(0));
    std::iota(v.begin(), v.end(), 0);

    for (auto _ : state)
    {
        //current function under benchmarking
        benchmark::DoNotOptimize(search::binarySearch(v, 0, v.size(), v.size()+1));
    }
    state.SetComplexityN(state.range(0));
}

BENCHMARK(BM_binary_search_worstCase)->RangeMultiplier(2)->Range(1<<5, 1<<18)->Complexity();

BENCHMARK_MAIN();
