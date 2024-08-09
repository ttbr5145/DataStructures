
#include "general.hpp"

#include <algorithm>
#include <vector>

using std::max;

constexpr int MAXN = 101;

//*最长上升子序列
template<typename T>
int LIS(T it, const T end)
{
    int Len=0, d[end-it+1];
    d[0] = *it;
    while (++it!=end)
    {
        if (*it > d[Len])
            d[++Len] = *it;
        else
            *std::lower_bound(d, d+Len, *it) = *it;
    }
    return Len+1;
}
//*最长不上升子序列
template<class T>
int LuS(T it, const T end)
{
    int Len=1, d[std::distance(it, end)];
    d[0] = *it;
    while (++it!=end)
    {
        if (*it<=d[Len-1])
            d[Len++] = *it;
        else
            *std::upper_bound(d, d+Len, *it, std::greater<int>{}) = *it;
    }
    return Len;
}

template<typename T>
int LCS(const T *s1, int l1, const T *s2, int l2)
{
    int lcs_len=0, dp[MAXN][l2];
    for (int i=0; i<l2; ++i) dp[0][i]=0;
    for (int i=1; i<l1; ++i) dp[i][0]=0;
    for (int i=0; i<l1; ++i)
        for (int j=0; j<l2; ++j)
        {
            if (s1[i]==s2[j])
                dp[i][j] = dp[i-1][j-1] + 1;
            else
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            _max(lcs_len, dp[i][j])
        }
    return lcs_len;
}


template <class CharT = char>
class KMP_Patern_basic
{
    int len_;
    const CharT *p;
    std::vector<int> f{};

public:
    void compile(const CharT *s, int lens)
    {
        this->p = s;
        this->len_ = lens;
        f.resize(len_);
        f[0] = -1;
        for (int i=1, j=-1; s[i]; ++i)
        {
            while (j>=0 && s[j+1] != s[i])
                j = f[j];
            if (s[j+1] == s[i])
                ++j;
            f[i] = j;
        }
    }

    template <class Call_Back>
    unsigned kmp(const CharT *t, Call_Back call_back=nullptr) const noexcept
    {
        int cnt=0, j=-1;
        for (int i=0; t[i]; ++i)
        {
            while (j>=0 && p[j+1] != t[i])
                j = f[j];
            if (p[j+1] == t[i]) {
                ++j;
                if (j+1 == len_) {
                    j=f[j];
                    ++cnt;
                    call_back(i-len_+1);
                }
            }
        }
        return cnt;
    }
};

typedef KMP_Patern_basic<char> KMP_Patern;