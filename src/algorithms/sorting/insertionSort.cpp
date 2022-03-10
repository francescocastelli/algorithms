#include "sorting.h"

namespace sorting 
{
int insertionSort(std::vector<int> &v)
{
    for (int j = 1; j < v.size(); j++)
    {
        auto key = v[j];
        auto i = j-1;

        while ( i >= 0 && v[i] > key ) 
        {   
            v[i+1] = v[i];
            i-=1;
        }

        v[i+1] = key;
    }

    return 0;
}
} // namespace sorting
