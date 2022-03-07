#include "search.h"

namespace search {

int binarySearch(std::vector<int> &v, int lower, int upper, int el)
{
    if ( upper >= lower )
    {
        int middle = int((upper-lower)/2 + lower);

        if ( v[middle] == el ) 
            return middle;

        if ( el < v[middle] )
            return binarySearch(v, lower, upper=middle-1, el);
        else 
            return binarySearch(v, middle+1, upper, el);
    }
    return -1;
}

}
