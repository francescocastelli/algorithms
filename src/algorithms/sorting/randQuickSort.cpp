#include "sorting.h"
#include "utils.h"

namespace sorting
{
int randQuicksort(std::vector<int> &v, int p, int q)
{
   if ( p < q ) 
   {
        int r = utility::randPartition(v, p, q);
        quicksort(v, p, r-1);
        quicksort(v, r+1, q);
   }

   return 0;
}
} // namespace sorting
