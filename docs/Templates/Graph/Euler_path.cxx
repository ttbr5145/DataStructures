
#include <vector>

constexpr int MAXN=1e5+2, MAXM=2e5+2;

int n, m;
std::vector<std::vector<int>> g; // 点编号从1开始

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
