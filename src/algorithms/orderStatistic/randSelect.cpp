#include "utils.h"
#include "orderStatistic.h"

namespace orderStatistics
{
int randSelect(std::vector<int> v, int p, int q, int i)
{
    if ( p == q ) return v[p];

    int r = utility::randPartition(v, p, q);
    int k = r - p + 1;
    
    if ( k == i ) return v[r];
    
    if ( i < k ) 
        return randSelect(v, p, r-1, i);

    return randSelect(v, r+1, q, i-k);
}
} // namespace orderStatistic
