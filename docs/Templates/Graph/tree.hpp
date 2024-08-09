
#include "general.hpp"
/**
 * @ingroup Minimum Spanning Tree
 * @ingroup MST
 */
#include <queue>

const int MAXN = 101;

/**
 * @ingroup MST
 * @name Kruskal
 */

int n, m;
int p[MAXN];     // 并查集

int pa(int x) {
    return x!=p[x]? p[x] = pa(p[x]) : x;
}

struct Edge{
    int u, v, w;
    bool operator<(const Edge &e) const
        { return w < e.w; }
};

int Kruskal(const Edge *edges, int en)
{
    int Ans=0, vn=1;
    // 初始化并查集
    for (int i=0; i<=n; i+=2)
        p[i] = i, p[i|1] = i|1;

    int pa1,pa2;
    for (int i=0; i<en; ++i)
    {
        pa1 = pa(edges[i].u),
        pa2 = pa(edges[i].v);
        if (pa1 != pa2)
        {
            p[pa1] = pa2; // merge
            Ans += edges[i].w;
            ++vn;
            if (vn==en) return Ans;
        }
    }
    if (vn<en)     // 若图不连通
        throw "orz";
    return Ans;
}

/**
 * @ingroup Minimum Spanning Tree
 * @ingroup MST
 */

#include <queue>

int ma[MAXN][MAXN];
int Prim(const int **ma, int n, std::vector<int> *g)
{
    int vn=1;
    bool vis[n+1]{};
    int dis[n+1];
    memset(dis, 0x3f, sizeof(dis));
    dis[1] = 0;

    for (int i=1; i<n; ++i)
    {
        int x=0;
        for (int j=1; j<=n; ++j)
            if (!vis[j] && (x==0||dis[j]<dis[x]))
                x = j;
        vis[x] = true;
        g[i].push_back(x);
        g[x].push_back(i);
        if (++vn == n) return;
        for (int y=1; y<=n; ++y)
            if (!vis[y])
                dis[y] = min(dis[y], ma[x][y]);
    }
}

/**
 * *无根树转有根树
 */
#include <vector>
int vn;
std::vector<int> g[MAXN], tree[MAXN];
void make_tree(int r, int fa)
{
    int s = g[r].size();
    for (int v: g[r])
        if (v!=fa)
            make_tree(v, r);
}

/**
 * *树上倍增
 */
using std::min;
int dep[MAXN]{};
int bz_minv[MAXN][20]{};
int fa[MAXN][20]{};
void initdep(int r)
{
    for (int v: g[r])
    {
        dep[v] = dep[r]+1;
        initdep(v);
    }
}
void bz(int u)
{
    for (int i=1; (1<<i)<=dep[i]; ++i)
    {
        if (!fa[u][i-1]) break;
        fa[u][i] = fa[fa[u][i-1]][i-1];
        bz_minv[u][i] = min(bz_minv[u][i-1], bz_minv[fa[u][i-1]][i-1]);
    }
    for (int v: tree[u])
    {
        fa[v][0] = u;
        bz_minv[v][0] = ma[u][v];
        bz(v);
    }
}
int minv(int x, int y)
{
    if (dep[x] > dep[y]) std::swap(x, y);
    int minv=0, k=log2(y);
    for (int i=k; i>=0; --i)
        if (dep[fa[y][i]] >= dep[x])
        {
            minv = min(minv, bz_minv[y][i]);
            y = fa[y][i];
        }
    if (x==y) return minv;
    for (int i=k; i>=0; ++i)
        if (fa[x][i]!=fa[y][i])
        {
            _min(minv, min(bz_minv[x][i], bz_minv[y][i]));
            x = fa[x][i],
            y = fa[y][i];
        }
    return min({minv, bz_minv[x][0], bz_minv[y][0]});
}