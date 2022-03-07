#include "orderStatistic.h"

namespace orderStatistic
{
int maximum(std::vector<int> &v)
{
    int max = v[0];

    for (auto el : v)
        if (el > max) 
            max = el;

    return max;
}
} // namespace orderStatistic
