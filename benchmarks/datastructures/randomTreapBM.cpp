#include <iostream>
#include <numeric>
#include <bits/stdc++.h> 
#include <benchmark/benchmark.h>
#include "randomTreap.h"

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
		    treap.insert(v[i%v.size()]);
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

    auto i = 0;
    for (auto _ : state)
    {
        //current function under benchmarking
		    treap.search(v[i%v.size()]);
        ++i;
    }

    state.SetComplexityN(state.range(0));
}

BENCHMARK(BM_RandomTreapSearch)
	->RangeMultiplier(2)
	->Range(1<<5, 1<<18)
	->Complexity(benchmark::oLogN);

//and call the main of the benchmark
BENCHMARK_MAIN();
