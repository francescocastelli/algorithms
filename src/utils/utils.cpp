#include "utils.h"
#include <numeric>
#include <random>
#include <bits/stdc++.h> 

namespace utility
{

int randomNumber(int lower, int upper)
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(lower, upper);

    return dist(rng);
}

int randPartition(std::vector<int> &v, int p, int q)
{
    int pivotIndex = p;
    int startPivotPos = randomNumber(p, q);
    int pivot = v[startPivotPos];
    int t;

    //swap the pivot and the first pos
    v[startPivotPos] = v[p];
    v[p] = pivot;

    for (auto j = p+1; j<=q; ++j)
    {
        if ( v[j] <= pivot ) 
        {
            ++pivotIndex;
            t = v[j];
            v[j] = v[pivotIndex];
            v[pivotIndex] = t;
        }
    }

    v[p] = v[pivotIndex];
    v[pivotIndex] = pivot;

    return pivotIndex;
}

int partition(std::vector<int> &v, int p, int q)
{
    int pivotIndex = p;
    int pivot = v[p];
    int t;

    for (auto j = p+1; j<=q; ++j)
    {
        if ( v[j] <= pivot ) 
        {
            ++pivotIndex;
            t = v[j];
            v[j] = v[pivotIndex];
            v[pivotIndex] = t;
        }
    }

    v[p] = v[pivotIndex];
    v[pivotIndex] = pivot;

    return pivotIndex;
}
}
