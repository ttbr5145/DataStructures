
#include <cmath>
#include <vector>

#include "math.hpp"

using cy::ceil_log2;

template<typename T, class op>
class zkwtree
{
protected:
    std::size_t N;
    std::vector<T> tr;

public:
    typedef std::size_t size_t;

    zkwtree() {}
    zkwtree(size_t n)
        :N(1 << std::size_t(ceil_log2(n)))
        { tr.resize(N<<1|1); }
    void resize(size_t size)
    {
        N = 1 << std::size_t(ceil_log2(size));
        tr.resize(N<<1|1);
    }

    T& operator[](size_t x)
        { return tr[x+N]; }
    void build()
    {
        for (auto i=N-1; i; --i)
            tr[i] = op{}(tr[i<<1], tr[i<<1|1]);
    }
    void build(size_t size, T* p)
    {
        resize(size);
        for (auto i=1; i<=size; ++i, ++p)
            operator[](i) = *p;
        build();
    }

    void update(size_t x, T n)
    {
        for (x+=N; x; x>>=1)
            tr[x] = op{}(tr[x], n);
    }

    T query(size_t l, size_t r) const
    {
        T ans(0);
        for (l+=N-1, r+=N+1; l^r^1; l>>=1, r>>=1)
        {
            if (!(l&1)) ans = op{}(ans, tr[l^1]);
            if (r & 1)  ans = op{}(ans, tr[r^1]);
        }
        return ans;
    }
};
