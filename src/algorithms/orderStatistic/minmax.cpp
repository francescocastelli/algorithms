#include "orderStatistic.h"

namespace orderStatistics
{
int minmax(std::vector<int> &v, int& minOut, int& maxOut)
{
    int min, max, i;

    if (v.size() % 2 != 0)
    {
        min = v[0];
        max = v[0];
        i = 1;
    }
    else if ( v[0] > v[1] )
    {
        min = v[1];
        max = v[0];
        i = 2;
    }else
    {
        min = v[0];
        max = v[1];
        i = 2;
    }
   
    while ( i < v.size() )
    {
        if ( v[i] < v[i+1] )
        {
            if ( v[i] < min ) min = v[i];
            if ( v[i+1] > max) max = v[i+1];
        }
        else
        {
            if ( v[i+1] < min ) min = v[i+1];
            if ( v[i] > max) max = v[i];
        }
        
        i+=2;
    }
   
    minOut = min;
    maxOut = max; 
    return 0;
}
} // namespace orderStatistic
