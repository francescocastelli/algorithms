#include "sorting.h"

namespace sorting 
{
int insertionSort(std::vector<int> &v)
{
    int i, j, key, n = v.size();

    for ( j = 1; j<n; j++)
    {
        key = v[j];
        i = j-1;

        while ( i > 0 && v[i] > key ) 
        {   
            v[i+1] = v[i];
            i-=1;
        }

        v[i+1] = key;
    }

    return 0;
}
} // namespace sorting
