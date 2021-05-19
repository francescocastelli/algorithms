//g++ test.cpp -std=c++11 -isystem benchmark/include -Lbenchmark/build/src -lbenchmark -lpthread -o benchmark_res
#include <iostream>
#include <numeric>
#include <bits/stdc++.h> 
#include <benchmark/benchmark.h>
#include "../include/datastructures.h"

static void BM_RandomTreapInsertion(benchmark::State& state) 
{
    datastruct::RandomTreap treap;

    std::vector<int> v (state.range(0));
    std::iota(v.begin(), v.end(), 0);
    std::random_shuffle(v.begin(), v.end());
	int i = 0;

    for (auto _ : state)
    {
        //current function under benchmarking
		benchmark::DoNotOptimize(treap.insert(i));
		++i;
    }

    state.SetComplexityN(state.range(0));
}

BENCHMARK(BM_RandomTreapInsertion)
	->RangeMultiplier(2)
	->Range(1<<5, 1<<18)
	->Complexity(benchmark::oLogN);

static void BM_RandomTreapSearch(benchmark::State& state) 
{
    datastruct::RandomTreap treap;

    std::vector<int> v (state.range(0));
    std::iota(v.begin(), v.end(), 0);
    std::random_shuffle(v.begin(), v.end());

	for (int i = 0; i<v.size(); ++i)
		treap.insert(v[i]);

    for (auto _ : state)
    {
        //current function under benchmarking
		treap.search(3);
    }

    state.SetComplexityN(state.range(0));
}

BENCHMARK(BM_RandomTreapSearch)
	->RangeMultiplier(2)
	->Range(1<<5, 1<<18)
	->Complexity(benchmark::oLogN);
//and call the main of the benchmark
BENCHMARK_MAIN();
