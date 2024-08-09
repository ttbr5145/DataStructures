
constexpr int MAXN = 101;

struct Edge
{
    int v, nxt=-1;
};

int n;
int cnt=0, hd[MAXN];
Edge ed[MAXN];

inline void add_ed(int u, int v)
{
    ++cnt;
    ed[cnt] = {v, hd[u]};
    hd[u] = cnt;
}

inline void add_eds(int x, int y)
{
    add_ed(x, y);
    add_ed(y, x);
}


int _p[MAXN];
void init_set(int n)
{
    for (int i=0; i<=n; i+=2)
        _p[i]=i, _p[i|1]=i|1;
}
int pa(int x)
{
    return x!=_p[x]? _p[x]=pa(_p[x]) : x;
}
inline void merge(int x, int y)
  { _p[pa(x)] = pa(y); }

#include <queue>
int dep[MAXN];
int fa[MAXN][21]{};
void LCA_init(int r)
{
    dep[r] = 1;
    std::queue<int> q;
    q.push(r);
    while (q.size())
    {
        int u = q.front();
        q.pop();
        for (int i=1; i<=20; ++i)
            fa[u][i] = fa[fa[u][i-1]][i-1];
        for (int i=hd[i]; ~i; i=ed[i].nxt)
        {
            int v = ed[i].v;
            if (dep[v]) continue;
            fa[v][0] = u;
            dep[v] = dep[u]+1;
            q.push(v);
        }
    }
}

int LCA(int x, int y)
{
    if (dep[x]>dep[y]) std::swap(x, y);
    for (int i=20; i>=0; --i)
        if (dep[fa[x][i]]>=dep[y])
            x = fa[x][i];

    for (int i=20; i>=0; --i)
        if (fa[x][i]!=fa[y][i])
            x=fa[x][i], y=fa[y][i];

    return x==y? x : -1;
}

int main()
{

}