#include "sorting.h"
#include <algorithm>

namespace sorting 
{
//compute k as the max number in the vector
int countingSort(std::vector<int> &a)
{
    std::vector<int> b (a.size(), 0);
    int max = *std::max_element(a.begin(), a.end());

    std::vector<int> c (max+1, 0); 
    
    for (auto i : a)
        c[i]+=1;

    for (auto i = 1; i<=max; ++i)
        c[i] += c[i-1];

    for (int i = b.size()-1; i>=0; --i)
    {
        b[c[a[i]]-1] = a[i];
        --c[a[i]];
    }

    a = std::move(b);
    return 0;
} 
} // namespace sorting
