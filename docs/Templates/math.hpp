
#include <cmath>
#include <cstdint>

namespace cy
{

template<class T>
constexpr void swap(T& a, T& b)
    { a^=b^=a^=b; }

template<class T>
constexpr T gcd(T a, T b)
{
    while (a%=b)
        swap(a, b);
    return b;
}

/**
 * @brief solve ax + by == gcd(a,b)
 * @param a_b two number to be used in gcd(a, b)
 * @param x_y a pair that satisfies ax + by == gcd(a,b)
 * @return gcd(a, b)

 a%b == a - a/b*b

  x*a + y*b
 = gcd(a, b)
 = gcd(b, a%b)
 = x*b + y*a%b
 = x*b + y*(a-a/b*b)
 = x*b + y*a - a/b*y*b
 = y*a + (x-a/b*y)*b

 => x*a +    y    * b
 * 在每次辗转中加入 [x,y] = [y, x-a/b*y] 即可
 */

template <class T>
T exgcd(T a, T b, T& x, T& y)
{
	if (!b) {
		x=1, y=0;
		return a;
	}
	auto d = exgcd(b, a%b, y, x);
	y -= a/b*x;
	return d;
}

template <class T, class Tr>
Tr qpow(T x, T n, Tr mod)
{
	Tr ret=1, res=x;
	while (n)
	{
		if (n&1)
			ret = ret*res%mod;
		res = res*res%mod;
		n >>= 1;
	}
	return ret;
}

//*逆元
template<class T>
constexpr T inv(T n, T p){
    return qpow(n, p-2, p);
}

constexpr int abs(int n)
{
    int const mask = n >> sizeof(int) * 8 - 1;
    return (n ^ mask) - mask;
}
constexpr int abs2(int n)
{
    int t{n>>31};
    return (n+t)^t;
}

namespace bits
{
    constexpr auto popcnt(unsigned n)
        { return __builtin_popcount(n); }
    constexpr auto popcnt(unsigned long n)
        { return __builtin_popcountl(n); }
    constexpr auto popcnt(unsigned long long n)
        { return __builtin_popcountll(n); }

    constexpr auto ctz(unsigned n)
        { return __builtin_ctz(n); }
    constexpr auto ctz(unsigned long n)
        { return __builtin_ctzl(n); }
    constexpr auto ctz(unsigned long long n)
        { return __builtin_ctzll(n); }

    constexpr auto clz(unsigned n)
        { return __builtin_clz(n); }
    constexpr auto clz(unsigned long n)
        { return __builtin_clzl(n); }
    constexpr auto clz(unsigned long long n)
        { return __builtin_clzll(n); }
}

constexpr int log2(std::int32_t n) {
    return 31 - bits::clz(static_cast<std::uint32_t>(n));
}
constexpr int log2(std::int64_t n) {
    return 63 - bits::clz(static_cast<std::uint64_t>(n));
}

constexpr int ceil_log2(std::int32_t n) {
    int clz = bits::clz(static_cast<std::uint32_t>(n));
    int ctz = bits::ctz(static_cast<std::uint32_t>(n));
    return 31 - clz + (clz+ctz!=31);
}

template <class T, class Tr>
constexpr Tr fact(T n, Tr mod)
{
    Tr v=1;
    while (n--) {
        v = v*n%mod;
    }
    return v;
}

template <class T, class Tr=T>
constexpr Tr A(T n, T m)
{
    Tr v=1;
    for (T i=n; i>m; --i)
        v *= i;
    return v;
}

template <class T, class Tr>
constexpr T C(T n, T m, Tr p)
{
    if (n < m) return 0;
    if (m > n-m) m = n-m;
    Tr a=1, b=1;
	for(int i=0; i<m; ++i){
		a = (a*(n-i))%p;
		b = (b*(i+1))%p;
	}
	return a * qpow(b,p-2, p) % p;
    // return fact(n, p) * inv(fact(m, p), p) % p * inv(fact(n-m, p), p) % p;
}

template <class T, class Tr>
constexpr Tr Lucas(T n, T m, Tr p)
{
    return m==0? 1 :
        Lucas(n/p, m/p, p) * C(n%p, m%p, p) % p;
}

}