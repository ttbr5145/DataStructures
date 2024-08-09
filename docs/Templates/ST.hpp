
#include <iostream>
#include <random>

#include "math.hpp"

using std::max;
using cy::log2;

constexpr int MAXN = 100;

template<class Type>
class ST
{
    int n_;
    Type st[18][MAXN+1]{}; //$2^17 = 131072$

public:
    ST(int n) :n_(n) {}

    Type& operator[](int x)
      { return st[0][x]; }

    template <class Tp>
    void init(Tp a, int n)
    {
        n_ = n;
        for (int i=1; i<=n; ++i)
            st[0][i] = *a++;
        init();
    }
    void init()
    {
        for (int j=1; j<18; ++j)
            for (int i=1; i+(1<<j)-1 <= n_ ; ++i)
                st[i][j] = max(st[j-1][i], st[j-1][i+(1<<(j-1))]);
    }

    Type query(int l, int r) const
    {
        auto k = log2(r-l+1);
        return max(st[k][l], st[k][r -(1<<k) +1]);
    }
};

/**
 @code
int main()
{
    Log2_init(MAXN);
    using namespace std;

    std::mt19937 rd(std::random_device{}());
    std::uniform_int_distribution<> dist(-100, 100);

    int n=10;
    ST<int> st;

    for (int i=1; i<=n; ++i)
        cout << (st[i] = dist(rd)) << ' ';

    st.n_ = n;
    st.init();

    cout << '\n' << st.query(1,n) << std::ends;
    for (int i=1; i<100; ++i)
        printf("%d ", log2(i));
}
 @endcode
*/