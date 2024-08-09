/**
 * 求欧拉路径（欧拉回路）
 * 算法：Hierholzer
*/

#include <cstdio>
#include <vector>
#include <algorithm>

template<typename T=int>
T rd()
{
    T n; char c=getchar();
    while (c<'0'||'9'<c)
        c = getchar();
    n = c-'0';
    while (c=getchar(), '0'<=c&&c<='9')
        n = n*10 + (c-'0');
    return n;
}

constexpr int MAXN=1e5+2, MAXM=2e5+2;

int n, m;
std::vector<std::vector<int>> g;

void Input()
{
    n=rd(); m=rd();
    g.resize(n+1);
    for (int i=0; i<m; ++i)
        g[rd()].push_back(rd());
    for (auto& v: g)
        std::sort(v.begin(), v.end());
}
int check() // 返回起点，若为0则没有欧拉路径
{
    struct {
        int in, out;
    }du[MAXN]{};
    for (int i=1; i<=n; ++i) {
        du[i].out += g[i].size();
        for (int j: g[i])
            ++du[j].in;
    }
    for (int i=1; i<=n; ++i)
    {
        if (du[i].in > du[i].out) {
            if (du[i].in -1 == du[i].out && du[0].in==0)
                du[0].in = i;
            else return 0;
        }
        else if (du[i].in < du[i].out) {
            if (du[i].in +1 == du[i].out && du[0].out==0)
                du[0].out = i;
            else return 0;
        }
    }
    return du[0].out? du[0].out : 1;
}
int sta[MAXN]{};
int cw=0, way[MAXM];
void Euler(int s)   // Hierholzer
{

    for (int end=g[s].size(); sta[s]<end;)
    {
        Euler(g[s][sta[s]++]);
    }
    way[cw++] = s;
}

int main()
{
    Input();
    int s = check();
    if (s==0) {
        printf("No");
        return 0;
    }
    Euler(s);
    for (int i=cw-1; i>=0; --i)
        printf("%d ", way[i]);
}