
static const int MAXN = 101, MAXM = 201;

class Graph
{
public:
    struct Edge{
        int v, w, nxt;
        bool operator<(const Edge &e) const
          { return w < e.w; }
        bool operator>(const Edge &e) const
          { return w > e.w; }
// # if __cplusplus >=202002L
# if __cpp_impl_three_way_comparison >= 201907L
        auto operator<=>(const Edge& e) const
          { return w<=>e.w; }
# endif
    };
    int vn=0, en=0, hd[MAXN]{};
    Edge ed[MAXN];

    void add_edge(int u, int v, int w)
    {
        ++en;
        ed[en] = {v, w, hd[u]};
        hd[u] = en;
    }
    void add_edges(int x, int y, int w)
    {
        add_edge(x, y, w);
        add_edge(y, x, w);
    }

}G;

#include <queue>

typedef std::pair<int,int> pii;
int dist[MAXN];

/**
 * @name Dijkstra
 * @brief O((n+m)logn)
 * @param s 起始位置
 *
 */
void Dijkstra(Graph& G, int s)
{
    using Edge = Graph::Edge;
    memset(dist, 0x3f, sizeof(dist));
    dist[s] = 0;
    std::priority_queue<pii, std::vector<pii>, std::greater<pii> > q;
    q.emplace(0, s);
    bool vis[MAXN]{};
    while (!q.empty())
    {
        int d = q.top().first;
        int u = q.top().second;
        q.pop();
        if (vis[u] || d != dist[u]) continue;
        vis[u] = true;
        for (int i=G.hd[u]; i; i=G.ed[i].nxt){
            Edge e = G.ed[i];
            if (!vis[e.v] && dist[e.v] > dist[u]+e.w){
                dist[e.v] = dist[u] + e.w;
                q.emplace(dist[e.v], e.v);
            }
        }
    }
}

/** @brief a sample of algorithm Dijkstra
 @code
#include <iostream>
int main()
{
    Graph G;
    G.add_edges(1, 2, 1);
    G.add_edges(2, 3, 2);
    G.add_edges(2, 4, 3);
    G.add_edges(3, 4, 2);
    G.add_edges(1, 3, 3);
    Dijkstra(G, 1);
    for (int i=1; i<=4; ++i)
        std::cout << dist[i] << ' ';
}
 @endcode
*/

#include <bitset>

bool SPFA(Graph& G, int s)
{
    auto &ed = G.ed;
    memset(dist, 0x3f, sizeof(dist));
    dist[s] = 0;
    std::queue<int> q;
    //bool inq[MAXN]{};
    std::bitset<MAXN> inq{};
    std::int_fast16_t cnt[MAXN]{};
    q.push(s);
    inq[s] = 1;
    cnt[s] = 1;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        inq[u] = 0;
        for (int i=G.hd[u]; i; i=G.ed[i].nxt)
        {
            int v = G.ed[i].v;
            if (dist[v] > dist[u] + ed[i].w) {
                dist[v] = dist[u] + ed[i].w;
                if (!inq[v]) {
                    if (++cnt[v] >= G.vn)
                        return false; // 有负环
                    q.push(v);
                    inq[v] = 1;
                }
            }
        }
    }
    return true;
}