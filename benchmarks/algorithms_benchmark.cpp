//g++ test.cpp -std=c++11 -isystem benchmark/include -Lbenchmark/build/src -lbenchmark -lpthread -o benchmark_res
#include <iostream>
#include <numeric>
#include <bits/stdc++.h> 
#include <benchmark/benchmark.h>
#include "../include/algorithms.h"

//BINARY SEARCH

//worst case binary search
static void BM_binary_search_worstCase(benchmark::State& state) 
{
    std::vector<int> v (state.range(0));
    std::iota(v.begin(), v.end(), 0);

    for (auto _ : state)
    {
        //current function under benchmarking
        benchmark::DoNotOptimize(binarySearch(v, 0, v.size(), v.size()+1));
    }
    state.SetComplexityN(state.range(0));
}

//BENCHMARK(BM_binary_search_worstCase)->RangeMultiplier(2)->Range(1<<5, 1<<18)->Complexity();

//POWERING A NUMBER 
static void BM_numberPowering(benchmark::State& state) 
{
    int a = rand() % 100;

    for (auto _ : state)
    {
        //current function under benchmarking
        benchmark::DoNotOptimize(numberPowering(a, state.range(0)));
    }
    state.SetComplexityN(state.range(0));
}

//BENCHMARK(BM_numberPowering)->RangeMultiplier(2)->Range(1<<2, 1<<20)->Complexity();

//STRASSEN
static void BM_strassen(benchmark::State& state) 
{
    int i, j; 
    lld** matB; 
    lld** matA;

    matB = new lld*[state.range(0)]; 
    matA = new lld*[state.range(0)];

    for (i = 0; i < state.range(0); i++) 
        matA[i] = new lld[state.range(0)]; 

    for (i = 0; i < state.range(0); i++)
        for (j = 0; j < state.range(0); j++)
            matA[i][j] = rand() % 100;

    for (i = 0; i < state.range(0); i++) 
        matB[i] = new lld[state.range(0)]; 

    for (i = 0; i < state.range(0); i++)
        for (j = 0; j < state.range(0); j++)
            matB[i][j] = rand() % 100;

    for (auto _ : state)
    {
        //current function under benchmarking
        benchmark::DoNotOptimize(Strassen(matA, matB, state.range(0), state.range(0), state.range(0)));
    }
    state.SetComplexityN(state.range(0));
}

//BENCHMARK(BM_strassen)->RangeMultiplier(2)->Range(1<<5, 1<<8)->Complexity();

static void BM_StringCompare(benchmark::State& state) 
{
    std::vector<int> v (state.range(0));
    std::iota(v.begin(), v.end(), 2);
    std::reverse(v.begin(), v.end());

    for (auto _ : state)
    {
        //current function under benchmarking
        benchmark::DoNotOptimize(sorting::bubble_sort(v));
    }
    state.SetComplexityN(state.range(0));
}

//BENCHMARK(BM_StringCompare)
//    ->RangeMultiplier(2)->Range(1<<5, 1<<20)->Complexity(benchmark::oN);

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

//BENCHMARK(BM_mergeSort)->RangeMultiplier(2)->Range(1<<2, 1<<20)->Complexity();

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

//BENCHMARK(BM_InsertionSort)->RangeMultiplier(2)->Range(1<<2, 1<<16)->Complexity();

static void BM_CountingSort(benchmark::State& state) 
{
    std::vector<int> v (state.range(0));
    std::iota(v.begin(), v.end(), 0);
    std::random_shuffle(v.begin(), v.end());

    for (auto _ : state)
    {
        //current function under benchmarking
        benchmark::DoNotOptimize(sorting::counting_sort(v));
    }

    state.SetComplexityN(state.range(0));
}

//BENCHMARK(BM_CountingSort)->RangeMultiplier(2)->Range(1<<2, 1<<16)->Complexity();

static void BM_RadixSort(benchmark::State& state) 
{
    std::vector<int> v (state.range(0));
    std::iota(v.begin(), v.end(), 0);
    std::random_shuffle(v.begin(), v.end());

    for (auto _ : state)
    {
        //current function under benchmarking
        benchmark::DoNotOptimize(sorting::radix_sort(v));
    }

    state.SetComplexityN(state.range(0));
}

//BENCHMARK(BM_RadixSort)->RangeMultiplier(2)->Range(1<<2, 1<<16)->Complexity();

static void BM_Quicksort(benchmark::State& state) 
{
    std::vector<int> v (state.range(0));
    //std::iota(v.begin(), v.end(), 0);
    //std::random_shuffle(v.begin(), v.end());
    for (int i = 0; i<v.size(); ++i)
        v[i] = utility::randomNumber(0, 10000);

    for (auto _ : state)
    {
        //current function under benchmarking
        benchmark::DoNotOptimize(sorting::quicksort(v, 0, v.size()-1));
    }

    state.SetComplexityN(state.range(0));
}

BENCHMARK(BM_Quicksort)->RangeMultiplier(2)->Range(1<<2, 1<<15)->Complexity();

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

//BENCHMARK(BM_minMax)->RangeMultiplier(2)->Range(1<<2, 1<<16)->Complexity();

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

//BENCHMARK(BM_randomSelect)->RangeMultiplier(2)->Range(1<<3, 1<<20)->Complexity();

//and call the main of the benchmark
BENCHMARK_MAIN();
