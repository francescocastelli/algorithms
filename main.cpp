#include <vector>
#include <iostream>
#include <algorithm>
#include "algorithms.h"

int main()
{
    std::vector<int> v (50);

    for (int i = 0; i<v.size(); ++i)
        v[i] = utility::randomNumber(0, 100);

    int rnd;

    rnd = utility::randomNumber(0, v.size()-1);
    std::cout << "alg: " << orderStatistics::randSelect(v, 0, v.size()-1, rnd) << '\n';
    std::sort(v.begin(), v.end());
    std::cout << "random i: " << rnd <<" correct val: " << v[rnd] << '\n';
}
