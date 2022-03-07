#include <iostream>
#include <numeric>
#include <bits/stdc++.h> 
#include <benchmark/benchmark.h>
#include "sorting.h"
#include "utils.h"

static void BM_RandQuicksort(benchmark::State& state) 
{
    std::vector<int> v (state.range(0));
    //std::iota(v.begin(), v.end(), 0);
    //std::random_shuffle(v.begin(), v.end());
    //
    for (int i = 0; i<v.size(); ++i)
        v[i] = utility::randomNumber(0, 10000);

    for (auto _ : state)
    {
        //current function under benchmarking
        benchmark::DoNotOptimize(sorting::randQuicksort(v, 0, v.size()-1));
    }

    state.SetComplexityN(state.range(0));
}

BENCHMARK(BM_RandQuicksort)->RangeMultiplier(2)->Range(1<<2, 1<<16)->Complexity(benchmark::oNLogN);

BENCHMARK_MAIN();
