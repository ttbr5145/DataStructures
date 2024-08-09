
#include <cstdio>
#include <iostream>

using std::uint32_t;
using std::uint64_t;

constexpr int MOD = 1e9+7;

template <uint32_t X, uint32_t Y, class T=int>
class Matrix
{
public:
    T a[X][Y]{};

    constexpr uint32_t rows()const{ return X; }
    constexpr uint32_t cols()const{ return Y; }

    auto& operator[](uint32_t i) noexcept
        { return a[i]; }

    template <uint32_t Y_>
    constexpr auto operator*(const Matrix<Y,Y_,T>& r) const noexcept
    {
        Matrix<X, Y_, T> res{};
        for (uint32_t i=0u; i<X; ++i)
            for (uint32_t j=0u; j<Y_; ++j) {
                res[i][j] = 0;
                for (uint32_t k=0u; k<Y; ++k)
                    res[i][j] = (res[i][j] + (long long)a[i][k]*r.a[k][j]%MOD) % MOD;
            }
        return res;
    }

    constexpr Matrix& operator*=(const Matrix<Y,Y,T>& r)
    {
        static_assert(X == Y);
        return *this = *this * r;
    }

    constexpr Matrix& pow(uint64_t n)
    {
        static_assert(X == Y);
        Matrix res = Identity<X,T>();
        while (n > 0)
        {
            if (n&1)
                res *= *this;
            *this *= *this;
            n >>= 1;
        }
        return *this = res;
    }

    template <uint32_t N, class _T>
    static constexpr Matrix Identity() noexcept
    {
        Matrix<N, N, _T> I{};
        for (int i=0; i<N; ++i)
            I.a[i][i] = 1;
        return I;
    }
    static using Unit = Identity;
};

/*
  @code
int main()
{
    uint64_t n;
    std::cin >> n;
    Matrix<2,2> a{0, 1, 1, 1};
    a.pow(n-1);
    std::cout << a[1][1];
}
  @endcode
*/