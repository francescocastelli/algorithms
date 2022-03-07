#include "sorting.h"

namespace sorting
{
int bubbleSort(std::vector<int> &v)
{
    int i, j, a;
    
    for (i=0; i<v.size(); i++)
        for (j=0; j<v.size(); j++)
            if (v[i] > v[j])
            {
                a = v[j];
                v[j] = v[i];
                v[i] = a;
            }

    return 0;
}
} // namespace sorting
