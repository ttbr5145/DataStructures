
#include "general.hpp"
#include <memory.h>

template<class T>
constexpr void _min(T& a, const T& b)
    { if (a>b) a=b; }

constexpr int MAXN = 2e4+9, MAXM = 1e5+9;

int n;
int root;
int cnt=0, hd[MAXN];
struct Edge {
    int v, nxt=-1;
} ed[2*MAXM];

constexpr void init()
{
    memset(hd, -1, sizeof(hd));
}

constexpr void add_ed(int u, int v)
{
    ed[cnt] = {v, hd[u]};
    hd[u] = cnt;
    ++cnt;
}
constexpr void add_eds(int x, int y)
{
    add_ed(x, y);
    add_ed(y, x);
}

int num=0, dfn[MAXN]{}, low[MAXN];

bool is_bri[2*MAXM]{};
void tarjan_bridge(int x, int in_ed)
{
    dfn[x] = low[x] = ++num;
    for (int i=hd[x]; ~i; i=ed[i].nxt)
    {
        int v = ed[i].v;
        if (!dfn[v])
        {
            tarjan_bridge(v, i);
            _min(low[x], low[v]);
            if (dfn[x] < low[v])
                is_bri[i] = is_bri[i^1] = true;
        }
        else if (i != in_ed^1)
        {
            _min(low[x], dfn[v]);
        }
    }
}

bool cnt_cut=0, is_cut[MAXN]{};
void tarjan_cut(int x)
{
    dfn[x] = low[x] = ++num;
    int cnt=0;
    for (int i=hd[x]; ~i; i=ed[i].nxt)
    {
        int v = ed[i].v;
        if (!dfn[v])
        {
            tarjan_cut(v);
            _min(low[x], low[v]);
            if (dfn[x] <= low[v])
            {
                ++cnt;
                if ((x!=root || cnt>1) && !is_cut[x])
                    ++cnt_cut, is_cut[x] = true;
            }
        }
        else _min(low[x], dfn[v]);
    }
}

int main()
{
    n = rd();
    int m = rd();
    while (m--)
    {
        add_eds(rd(), rd());
    }

    root = 1;
    tarjan_cut(1);

    printf("%d\n", cnt_cut);
    for (int i=0; i<=n; ++i)
        if (is_cut[i])
            printf("%d ", i);
}