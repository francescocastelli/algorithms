#include <vector>
#include <iostream>
#include <algorithm>
#include "algorithms.h"

int main()
{
    std::vector<int> v (50);

    for (int i = 0; i<v.size(); ++i)
        v[i] = utility::randomNumber(0, 100);
    
    for ( auto el : v )
        std::cout << el << ' '; 

    std::cout << '\n';

    sorting::randQuicksort(v, 0, v.size()-1);
    for ( auto el : v ) 
        std::cout << el << ' ';
}
