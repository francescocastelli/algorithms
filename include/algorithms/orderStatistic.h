#include <vector>

namespace orderStatistics
{
    int minimum(std::vector<int> &v);
    int maximum(std::vector<int> &v);
    int minmax(std::vector<int> &v, int& minOut, int& maxOut);
    int randSelect(std::vector<int> v, int p, int q, int i);
}
