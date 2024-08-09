
#include "general.hpp"
#include <vector>
#include <queue>
#include <cmath>

constexpr int SIZE = 501;
int tot, t;
int fa[SIZE][20], dep[SIZE], dist[SIZE];
int vs, ver[2*SIZE], verv[2*SIZE], nxt[SIZE], edge[SIZE], head[SIZE];

void add_edge(int x, int y, int z)
{
    ++tot;
    ver[tot]=y;
    edge[tot]=z;
    nxt[tot]=head[x];
    head[x]=tot;
}
void add_edge_ver(int x, int y, int z)
{
    ++vs;
    verv[vs] = z;
    add_edge(vs, x, 1);
    add_edge(vs, y, 1);
    p[x] = vs;
    p[y] = vs;
}

int n, p[SIZE*2];
void init_set(int n)
{
    for (int i=0; i<=n; i+=2)
        p[i]=i, p[i|1]=i|1;
}
int pa(int x)
{
    return x==p[x]?
        x : (p[x]=pa(p[x]));
}

struct Edge{
    int u, v, w;
    bool operator<(const Edge &e) const
        { return w < e.w; }
};

void Kruskal_tree(const Edge *edges, int en)
{
    init_set(n*2);
    for (int i=0; i<en; ++i)
    {
        int pa1=pa(edges[i].u), pa2=pa(edges[i].v);
        if (pa1!=pa2)
        {
            add_edge_ver(pa1, pa2, edges[i].w);
        }
    }
}

//*树上倍增

void bfs()
{
    std::queue<int> q;
    q.push(1);
    dep[1]=1;
    while (q.size())
    {
        int x = q.front(); q.pop();
        for (int i=head[x]; i; i=nxt[i])
        {
            int y=ver[i];
            if (dep[y]) continue;
            dep[y] = dep[x]+1;
            dist[y] = dist[x] + edge[i];
            fa[y][0] = x;
            for (int j=1; j<=t; ++j)
                fa[y][j] = fa[fa[y][j-1]][j-1];
            q.push(y);
        }
    }
}

int LCA(int x, int y)
{
    if (dep[x] > dep[y])
        std::swap(x, y);
    for (int i=t; i>=0; --i)
        if (dep[fa[y][i]] >= dep[x])
            y = fa[y][i];
    if (x==y) return x;
    for (int i=t; i>=0; --i)
        if (fa[x][i]!=fa[y][i])
            x = fa[x][i],
            y = fa[y][i];
    return fa[x][0];
}

int minv(int x, int y)
{
    return pa(x)!=pa(y)? -1 : verv[LCA(x,y)];
}