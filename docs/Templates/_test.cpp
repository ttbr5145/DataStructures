
#include "general.hpp"
#include <iostream>
#include <cstdio>

template <typename T, typename Tr>
T qpow(T x, T n, Tr mod)
{
	Tr ans=1, res=x;
	while (n)
	{
		if (n&1)
			ans = (Tr)ans*res%mod;
		res = (Tr)res*res%mod;
		n >>= 1;
	}
	return ans;
}
template <typename T, typename Tr=T>
constexpr T C(T n, T m, Tr p)
{
    if (n < m) return 0;
    if(m > n-m) m = n-m;
    Tr a=1,b=1;
	for(int i=0;i<m;i++){
		a=(a*(n-i))%p;
		b=(b*(i+1))%p;
	}
	return a*qpow(b,p-2, p)%p;
}

template <typename T, typename Tr=T>
constexpr Tr Lucas(T n, T m, Tr p)
{
    return m==0? 1 :
        Lucas(n/p, m/p, p) * C(n%p, m%p, p) % p;
}
int main()
{
    int n=rd(), m=rd(), p=rd();
    // print(cy::fact(5));
    printf("%d", Lucas(n, m, (long long)p));
}