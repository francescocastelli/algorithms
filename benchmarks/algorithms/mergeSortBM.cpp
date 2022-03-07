#include <iostream>
#include <numeric>
#include <bits/stdc++.h> 
#include <benchmark/benchmark.h>
#include "sorting.h"

static void BM_mergeSort(benchmark::State& state) 
{
    std::vector<int> v; 

    for (int i=0; i<state.range(0); i++)
    {
        v.push_back(rand() % 100);
    }

    for (auto _ : state)
    {
        //current function under benchmarking
        benchmark::DoNotOptimize(sorting::mergeSort(v));
    }
    state.SetComplexityN(state.range(0));

}

BENCHMARK(BM_mergeSort)->RangeMultiplier(2)->Range(1<<2, 1<<20)->Complexity();

BENCHMARK_MAIN();
