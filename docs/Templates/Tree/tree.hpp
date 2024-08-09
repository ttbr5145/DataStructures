
constexpr int MAXN = 101;

struct Edge {
    int v, nxt=0;
};
int n;
int cnt=0, hd[MAXN];
Edge ed[MAXN];


#include <queue>

int dep[MAXN];
int _fa[MAXN][21]{};

void LCA_init(int rt)
{
    std::queue<int> q;
    q.push(rt);
    dep[rt] = 1;
    while (!q.empty())
    {
        int u = q.front(); q.pop();
        for (int i=hd[u]; i; i=ed[i].nxt)
        {
            int v=ed[i].v;
            if (dep[v]) continue;
            dep[v] = dep[u]+1;
            _fa[v][0] = u;
            for (int j=1; j<=20; ++j)
                _fa[v][j] = _fa[_fa[v][j-1]][j-1];
            q.push(v);
        }
    }
}

int LCA(int x, int y)
{
    if (dep[x]<dep[y]) std::swap(x, y);

    for (int i=20; i>=0; --i)
        if (dep[_fa[x][i]]>=dep[y])
            x = _fa[x][i];
    if (x==y) return x;

    for (int i=20; i>=0; --i)
        if (_fa[x][i]!=_fa[y][i])
            x=_fa[x][i], y=_fa[y][i];

    return _fa[x][0];
}


int _pa[MAXN];
int pa(int x)
{
    return x!=_pa[x]? _pa[x]=pa(_pa[x]) : x;
}
inline void merge(int x, int y)
    { _pa[pa(x)] = pa(y); }


int ans[MAXN];
// query[x][i].first表示有一个求LCA(x, query[x][i].first)的询问
// query[x][i].second表示这个询问的答案存储在ans[query[x][i].second]
typedef std::pair<int, int> pii;
std::vector<pii> query[MAXN];

enum {
	none=0,
	one,
	two
} vis[MAXN]{};

void tarjan_lca(int u)
{
	vis[u] = one;
	for (int i=hd[u]; i; i=ed[i].nxt)
	{
		int v = ed[i].v;
		if (vis[v]) continue;
		tarjan_lca(v);
        _pa[v] = u;
	}
    for (auto p: query[u])
		if (vis[p.first]==two)
			ans[p.second] = pa(p.first);
	vis[u] = two;
	/* for (auto [v, id]: query[u])
		if (vis[v]==two)
			ans[id] = pa(v); */
}