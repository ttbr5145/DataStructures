
#include <algorithm>
#include <memory.h>

void ranks(int *a, int *p, int len)
{
    std::sort(a, a+len);
    int *end = std::unique(a, a+len);
    for (int i=0; i<len; ++i)
        p[i] = std::upper_bound(a, end, a[i]) - a;
}