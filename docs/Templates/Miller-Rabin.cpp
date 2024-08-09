
#include <cstdio>
#include <cstdint>

typedef long long ll;

constexpr int qpow(int x, int n, int mod)
{
	int ans=1, res=x;
	while (n)
	{
		if (n&1)
			ans = (ll)ans*res%mod;
		res = (ll)res*res%mod;
		n >>= 1;
	}
	return ans;
}


constexpr auto ctz(unsigned int n)
	{ return __builtin_ctz(n); }
constexpr auto ctz(unsigned long n)
	{ return __builtin_ctzl(n); }
constexpr auto ctz(unsigned long long n)
	{ return __builtin_ctzll(n); }

template<typename T>
constexpr int ctz(T n)
{
	int cnt=0;
	while (!(n&1))
		n>>=1, ++cnt;
	return cnt;
}

int Miller_Rabin(std::uint32_t n)
{
	using std::uint32_t;
	if (n==2) return true;
	if (!(n&1) || n<=1)
		return false;
	//static constexpr uint64_t primes[]{2, 325, 9375, 28178, 450775, 9780504, 1795265022};
	static constexpr uint32_t primes[]{2, 7, 61};
	int crz=ctz(n-1), e=(n-1)>>crz;

	for (auto p: primes)
	{
		int v = qpow(p, e, n);
		if (v<=1 || v==n-1)
			continue;
		for (int i=1; i<=crz; ++i)
		{
			v = (std::uint64_t)v*v%n;
			if (v==n-1 && i!=crz)
			{
				v = 1;
				break;
			}
			if (v==1)
				return false;
		}
		if (v!=1)
			return false;
	}
	return true;
}
