#include <iostream>
#include <numeric>
#include <bits/stdc++.h> 
#include <benchmark/benchmark.h>
#include "skipList.h"

static void BM_SkipListInsertion(benchmark::State& state) 
{
    datastruct::SkipList skipList;

    std::vector<int> v (state.range(0));
    std::iota(v.begin(), v.end(), 0);
    std::random_shuffle(v.begin(), v.end());

	  auto i = 0;
    for (auto _ : state)
    {
        //current function under benchmarking
		    skipList.insert(v[i % v.size()]);
		    ++i;
    }

    state.SetComplexityN(state.range(0));
}

BENCHMARK(BM_SkipListInsertion)
	->RangeMultiplier(2)
	->Range(1<<5, 1<<18)
	->Complexity(benchmark::oLogN);

static void BM_SkipListSearch(benchmark::State& state) 
{
    datastruct::SkipList skipList;

    std::vector<int> v (state.range(0));
    std::iota(v.begin(), v.end(), 0);
    std::random_shuffle(v.begin(), v.end());

    for (int i = 0; i<v.size(); ++i)
        skipList.insert(v[i]);

    auto i = 0;
    for (auto _ : state)
    {
        //current function under benchmarking
		    skipList.search(v[i % v.size()]);
        ++i;
    }

    state.SetComplexityN(state.range(0));
}

BENCHMARK(BM_SkipListSearch)
	->RangeMultiplier(2)
	->Range(1<<5, 1<<18)
	->Complexity(benchmark::oLogN);

//and call the main of the benchmark
BENCHMARK_MAIN();
