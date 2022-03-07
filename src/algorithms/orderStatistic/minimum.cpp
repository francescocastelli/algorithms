#include "orderStatistic.h"

namespace orderStatistic
{
int minimum(std::vector<int> &v)
{
    int min = v[0];

    for (auto el : v)
        if (el < min) 
            min = el;

    return min;
}
} // namespace orderStatistic
