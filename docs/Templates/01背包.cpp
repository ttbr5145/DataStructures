// 01
#include "general.hpp"

int t, m;
struct {
	int t, v;
}d[101];
int f[1001]{};

int main()
{
	t = rd();
	m = rd();
	for (int i=0; i<m; ++i)
		d[i].t = rd(), d[i].v = rd();
	for (int i=0; i<m; ++i)
		for (int j=t; j>=d[i].t; --j)
			_max(f[j], f[j-d[i].t] + d[i].v);
	printf("%d", f[t]);
}
