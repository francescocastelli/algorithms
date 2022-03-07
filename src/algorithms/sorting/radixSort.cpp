#include "sorting.h"
#include <algorithm>

namespace sorting
{
int _counting_sort(std::vector<int> &a, int digitIndex)
{
    std::vector<int> b (a.size(), 0);
    //always 10 bc we consider one digit at the time
    std::vector<int> c (10, 0); 
    
    for (auto i : a)
        c[(i/digitIndex) % 10]+=1;

    for (auto i = 1; i<10; ++i)
        c[i] += c[i-1];

    for (int i = b.size()-1; i>=0; --i)
    {
        b[c[(a[i]/digitIndex) % 10]-1] = a[i];
        --c[(a[i]/digitIndex) % 10];
    }

    a = std::move(b);
    return 0;
}

int _numDigits(int number)
{
    int digits = 0;
    if (number < 0) digits = 1; 
    while (number) {
        number /= 10;
        digits++;
    }
    return digits;
}

int radixSort(std::vector<int> &v)
{
   int max = *std::max_element(v.begin(), v.end());
   int digitNum = _numDigits(max);
   int digitIndex = 1;

   for (auto i = 1; i <= digitNum; ++i)
   {
        _counting_sort(v, digitIndex);        
        digitIndex *= 10;
   }

   return 0;
}
} // namespace sorting
