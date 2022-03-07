#include "sorting.h"

namespace sorting
{
std::vector<int> _merge(std::vector<int> &v1, std::vector<int> &v2)
{
    int i = 0, j = 0, k = 0;
    std::vector<int> v;

    while ( i < v1.size() && j < v2.size() )
    {
        if ( v1[i] <= v2[j] )
        {
            v.push_back(v1[i]);
            i++;
        }else 
        {
            v.push_back(v2[j]); 
            j++;
        }
    }

    while ( i < v1.size() )
    {
        v.push_back(v1[i]);
        i++;
    }

    while( j < v2.size() )
    {
        v.push_back(v2[j]); 
        j++;
    }

    return v;
}

int mergeSort(std::vector<int> &v)
{
    std::vector<int> v1, v2;
    int n = v.size();

    if ( n == 1 ) return 0;
    
    for ( int i=0; i<v.size()/2; i++ )
        v1.push_back(v[i]);

    for ( int i=v.size()/2; i<v.size(); i++ )
        v2.push_back(v[i]);

    mergeSort(v1);
    mergeSort(v2);
    v = _merge(v1, v2);
}
} // namespace sorting
