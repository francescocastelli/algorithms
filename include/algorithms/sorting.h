#include <vector>

namespace sorting 
{
    int countingSort(std::vector<int> &a);
    int insertionSort(std::vector<int> &v);
    int quicksort(std::vector<int> &v, int p, int q);
    int randQuicksort(std::vector<int> &v, int p, int q);
    int mergeSort(std::vector<int> &v);
    int bubbleSort(std::vector<int> &v);
    int radixSort(std::vector<int> &v);
}
