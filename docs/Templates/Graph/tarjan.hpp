
#include <cstdint>
#include <algorithm>
#include <set>
#include <stack>
#include <vector>

using std::min;
typedef std::uint_fast32_t uint32_t;

static constexpr int MAXN = 101, MAXM = 2*MAXN;

class Graph
{
public:

    struct Edge {
        int u, v;
    };

    int n;
    int hd[MAXN]{};
    struct {
        int v, nxt=0;
    } ed[MAXM];

    void add_ed(int u, int v)
    {
        static int cnt=0;
        ++cnt;
        ed[cnt] = {v, hd[u]};
        hd[u] = cnt;
    }
    void add_eds(int x, int y)
    {
        add_ed(x, y);
        add_ed(y, x);
    }
};

using Edge = Graph::Edge;

int Root;

uint32_t dfn[MAXN], low[MAXN];

bool is_cut[MAXN]{};
std::vector<std::vector<int> > vdcc;

void tarjan_vDCC(const Graph& G, int u, int fa=0)   // 点双连通分量
{
    static uint32_t num=0;
    static std::stack<int> S;

    auto &hd{G.hd};
    auto &ed{G.ed};

    dfn[u] = low[u] = ++num;
    S.emplace(u); //

    if (u == Root && hd[u]==0)  // 孤立点
    {
        vdcc.emplace_back( u ); // 单点集
        return;
    }

    int children = 0;

    for (int i=hd[u]; i; i=ed[i].nxt)
    {
        int v = ed[i].v;
        if (v == fa) continue;
        // S.emplace(u, v);
        if (!dfn[v]) // 树边
        {
            tarjan_vDCC(G, v, u);
            low[u] = min(low[u], low[v]);

            if (low[v] >= dfn[u]) // u是割点
            {
                ++children;
                if (u!=Root || children > 1)
                    is_cut[u] = true;
                std::vector<int> s;
                int e;
                do {
                    e = S.top();
                    S.pop();
                    s.emplace_back(e);
                } while (e != v);
                s.emplace_back(u);
                vdcc.emplace_back(std::move(s));
            }
        }
        else //if (dfn[v] < dfn[u]) // 反向边
        {
            low[u] = min(low[u], dfn[v]);
        }
    }
}

void tarjan_eDCC(int u, int fa=0); // 边双连通分量


std::vector<std::vector<int> > scc;
uint32_t sccno[MAXN]{};

// 每个点只属于一个强连通分量

void tarjan_scc(const Graph& G, int u, std::stack<int> &S) // 强连通分量 —— 缩点
{
    static uint32_t num{0};

    auto &hd{G.hd};
    auto &ed{G.ed};

    dfn[u] = low[u] = ++num;
    S.emplace(u);

    for (int i=hd[u]; i; i=ed[i].nxt)
    {
        int v = ed[i].v;
        if (!dfn[v])
        {
            tarjan_scc(G, v, S);
            low[u] = min(low[u], low[v]);
        }
        else if (!sccno[v]) // 不要考虑已确定强连通分量编号的点
        {
            low[u] = min(low[u], dfn[v]);
        }
    }

    if (low[u] == dfn[u])
    {
        std::vector<int> c;
        const uint32_t No = 1 + scc.size();
        int v;
        do {
            v = S.top(); S.pop();
            sccno[v] = No;
            c.emplace_back(v);
        } while (v != u);
        scc.emplace_back(std::move(c));
    }
}
void search_scc(const Graph& G)
{
    std::stack<int> S;
    for (int i=1; i<=G.n; ++i)
        if (!sccno[i])
            tarjan_scc(G, i, S);
}
