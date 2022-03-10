#include <iostream>
#include <numeric>
#include <algorithm>
#include <bits/stdc++.h> 
#include <benchmark/benchmark.h>
#include "sorting.h"

static void BM_InsertionSort_worse_case(benchmark::State& state) 
{
    std::vector<int> v (state.range(0));
    std::iota(v.begin(), v.end(), 2);
    //worst case analysis for insertion sort -> reversed ordert input
    std::reverse(v.begin(), v.end());

    for (auto _ : state)
    {
        benchmark::DoNotOptimize(sorting::insertionSort(v));
    }
    state.SetComplexityN(state.range(0));
}

BENCHMARK(BM_InsertionSort_worse_case)->RangeMultiplier(2)->Range(1<<2, 1<<16)->Complexity(benchmark::oNSquared);

static void BM_InsertionSort_best_case(benchmark::State& state) 
{
    std::vector<int> v (state.range(0));
    std::iota(v.begin(), v.end(), 2);

    for (auto _ : state)
    {
        benchmark::DoNotOptimize(sorting::insertionSort(v));
    }
    state.SetComplexityN(state.range(0));
}

BENCHMARK(BM_InsertionSort_best_case)->RangeMultiplier(2)->Range(1<<2, 1<<16)->Complexity(benchmark::oN);

static void BM_InsertionSort_avg_case(benchmark::State& state) 
{
    std::vector<int> v (state.range(0));
    std::iota(v.begin(), v.end(), 2);

    // random vector
    auto rng = std::default_random_engine {};
    std::shuffle(v.begin(), v.end(), rng);

    for (auto _ : state)
    {
        benchmark::DoNotOptimize(sorting::insertionSort(v));
    }
    state.SetComplexityN(state.range(0));
}

BENCHMARK(BM_InsertionSort_avg_case)->RangeMultiplier(2)->Range(1<<2, 1<<16)->Complexity(benchmark::oNSquared);

BENCHMARK_MAIN();
