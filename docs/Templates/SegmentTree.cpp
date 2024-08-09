/// @file 线段树模板
/// 默认下标从1开始

#include <cstdint>
#include <algorithm>

using ll = long long;

int *val;  // values

template<int N>
class SegmentTree
{
protected:
    struct {
        int sum=0, plus=0;
    } tree[4*N];

    void up(int rt)
    {
        tree[rt].sum = tree[rt<<1].sum + tree[rt<<1|1].sum;
    }
    void down(int rt, int cl, int cr)
    {
        if (tree[rt].plus) {
            int plus = tree[rt].plus;
            tree[rt].plus = 0;
            const int L=rt<<1, R=rt<<1|1;
            int mid = (cl+cr)>>1;
            tree[L].sum += (mid-cl+1)*plus;
            tree[L].plus += plus;
            tree[R].sum += (cr-mid)*plus;
            tree[R].plus += plus;
        }
    }

public:
    void build(int cl=1, int cr=N, int rt=1)
    {
        if (cl==cr) {
            tree[rt].sum = val[cl];
            return;
        }
        int mid = (cl+cr)>>1;
        build(cl, mid, rt<<1);
        build(mid+1, cr, rt<<1|1);
        up(rt);
    }

    void plus(int l, int r, int add, int cl=1, int cr=N, int rt=1)
    {
        if (l==cl && r==cr){
            tree[rt].sum += (cr-cl+1)*add;
            tree[rt].plus += add;
            return;
        }
        down(rt, cl, cr);
        int mid = (cl+cr)>>1;
        plus(l, r, add, cl, mid, rt<<1);
        plus(l, r, add, mid+1, cr, rt<<1|1);
        up(rt);
    }

    int query(int l, int r, int cl=1, int cr=N, int rt=1)
    {
        if (l==cl && r==cr)
            return tree[rt].sum;
        down(rt, cl, cr);
        int mid = (cl+cr)>>1;
        if (r<=mid) return query(l, r, cl, mid, rt<<1);
        if (l>mid) return query(l, r, mid+1, cr, rt<<1|1);
        return query(l, r, cl, mid, rt<<1) + query(l, r, mid+1, cr, rt<<1|1);
    }
};
/*
 @code
int segment_tree()
{
    using namespace std;

    int n,m, c,x,y;
    ll k;
    cin >> n >> m;
    val = new int[n+2];
    for (int i=1; i<=n; ++i)
        cin >> val[i];
    SegmentTree t(n);
    t.build();
    delete val;

    while (m--){
        cin >> c >> x >> y;
        if (c==1){
            cin >> k;
            t.updata(x, y, k);
        }
        else{
            cout << t.query(x, y) << endl;
        }
    }
}
 @endcode
*/

constexpr int MAXMEM=1e8;

/**
 * @brief 可持久化数组
 *
 */
template <class T>
class PersArray
{
protected:
    int N, cnt{1};
    struct node {
        int ls, rs;
        T v;
    } tr[MAXMEM];
public:
    void build(int n)
        { N = n; build(1, n, 1); }
    void build(int l, int r, int rt=1) noexcept
    {
        if (l==r) {
            tr[rt].v = val[l];
            return;
        }
        tr[rt].ls = ++cnt;
        tr[rt].rs = ++cnt;
        int mid = (l+r)>>1;
        build(l, mid, tr[rt].ls);
        build(mid+1, r, tr[rt].rs);
    }
    /**
     * @brief modify a[i] to x, with rt the root of the version
     *
     * @param rt the root of the version
     * @param i index
     * @param x the value
     * @return int the new root of this modified version
     */
    [[nodiscard]] int modify(int rt, int i, int x)
        { return modify(rt, i, x, 1, N); }
    [[nodiscard]] int modify(int rt, int i, int x, int l, int r) noexcept
    {
        tr[++cnt] = tr[rt];
        rt = cnt;
        if (l==r)
            tr[rt].v = x;
        else {
            int mid = (l+r)>>1;
            if (i<=mid)
                tr[rt].ls = modify(tr[rt].ls, i, x, l, mid);
            else
                tr[rt].rs = modify(tr[rt].rs, i, x, mid+1, r);
        }
        return rt;
    }
    /**
     * @brief get a[x] with rt the root of the verison
     *
     * @param rt the root of the verison
     * @param i index
     */
    T get(int rt, int i)
        { return get(rt, i, 1, N); }
    T get(int rt, int i, int l, int r) const noexcept
    {
        if (l==r) return tr[rt].v;
        int mid = (l+r)>>1;
        if (i<=mid)
            return get(tr[rt].ls, i, l, mid);
        else
            return get(tr[rt].rs, i, mid+1, r);
    }
};

/**
 * @brief 可持久化并查集
 *
 */
namespace PerUFSet
{
int N, cnt{1};
struct node {
    int ls, rs;
} tr[5'000'000]; // 可以考虑用vector
struct data {
    int fa, rank;
} d[5'000'000];

namespace detail
{
void build(int l, int r, int rt=1)
{
    if (l==r) {
        d[rt]= {l, 1};
        return;
    }
    tr[rt] = {++cnt, ++cnt};
    int mid = (l+r)>>1;
    build(l, mid, tr[rt].ls);
    build(mid+1, r, tr[rt].rs);
}

int clone(int i)
{
    ++cnt;
    tr[cnt] = tr[i];
    d[cnt] = d[i];
    return cnt;
}
[[nodiscard]] int modifyfa(int rt, int i, int x, int l, int r)
{
    rt = clone(rt);
    if (l==r)
        d[rt].fa = x;
    else {
        int mid = (l+r)>>1;
        if (i<=mid)
            tr[rt].ls = modifyfa(tr[rt].ls, i, x, l, mid);
        else
            tr[rt].rs = modifyfa(tr[rt].rs, i, x, mid+1, r);
    }
    return rt;
}
/**
 * @param nl 记录modifyfa之前的cnt。若要访问的node的id<=nl，则该node是以前版本的，需要复制。
 */
void updaterank(int rt, int i, int nl, int l, int r)
{
    if (l==r) {
        d[rt].rank++;
        return;
    }
    int mid = (l+r)>>1;
    if (i<=mid) {
        if (tr[rt].ls<=nl) tr[rt].ls = clone(tr[rt].ls);
        updaterank(tr[rt].ls, i, nl, l, mid);
    }
    else {
        if (tr[rt].rs<=nl) tr[rt].rs = clone(tr[rt].rs);
        updaterank(tr[rt].rs, i, nl, mid+1, r);
    }
}

int getid(int rt, int i, int l, int r)
{
    if (l==r) return rt;
    int mid = (l+r)>>1;
    if (i<=mid)
        return getid(tr[rt].ls, i, l, mid);
    else
        return getid(tr[rt].rs, i, mid+1, r);
}
} // namespace detail

void build(int n) { N = n; detail::build(1, n, 1); }

int find(int rt, int x)
{
    int fid = detail::getid(rt, x, 1,N);
    return x==d[fid].fa? fid : find(rt, d[fid].fa);
}
[[nodiscard]] int merge(int rt, int u, int v)
{
    int fuid=find(rt, u), fvid=find(rt, v);
    if (fuid==fvid) return rt;
    if (d[fuid].rank > d[fvid].rank)
        std::swap(fuid, fvid);
    int nl = cnt;
    int new_rt = detail::modifyfa(rt, d[fuid].fa, d[fvid].fa, 1,N);
    detail::updaterank(new_rt, d[fvid].fa, nl, 1,N);
    return new_rt;
}
} // PerUFSet


///* 动态开点线段树
template<typename Type>
class AutoSegmentTree
{
public:
    static constexpr int MAXN = 1e5, L = -1e4, R = 1e4;

    struct node{
        int ls=0, rs=0;
        Type value=0, mark=0;
    } tree[MAXN];

protected:
    int cnt = 1;

    void _update(int i, Type add, int len)
    {
        tree[i].value += add * len;
        tree[i].mark += add;
    }
    void _down(int i, int len)
    {
        if (!tree[i].ls) tree[i].ls = ++cnt;
        if (!tree[i].rs) tree[i].rs = ++cnt;
        if (tree[i].mark)
        {
            _update(tree[i].ls, tree[i].mark, len>>1),
            _update(tree[i].rs, tree[i].mark, len-(len>>1));
            tree[i].mark = 0;
        }
    }

public:
    void plus(int l, int r, Type add, int i=1, int cl=L, int cr=R)
    {
        if (cl>=l && cr<=r)
            return _update(i, add, cr-cl+1);
        _down(i, cr-cl+1);
        int mid = (cr+cl-1)/2;
        if (mid >= l)
            plus(l,r,add, tree[i].ls, cl, mid);
        if (mid < r)
            plus(l,r,add, tree[i].rs, mid+1, cr);

        tree[i].value = tree[tree[i].ls].value + tree[tree[i].rs].value;
    }

    Type query(int l, int r, int i=1, int cl=L, int cr=R)
    {
        if (cl>=l && cr<=r)
            return tree[i].value;
        _down(i, cr-cl+1);
        int mid = (cr+cl-1)/2;
        if (mid >= r)
            return query(l,r, tree[i].ls, cl, mid);
        else if (mid < l)
            return query(l,r, tree[i].rs, mid+1, cr);
        else
            return query(l,r, tree[i].ls, cr, mid)
                 + query(l,r, tree[i].rs, mid+1, cr);
    }
};
/*
#include <random>
int autoSegmentTree()
{
    using namespace std;
    std::mt19937 rd(std::random_device{}());
    std::uniform_int_distribution<> dist(-100, 100);

    AutoSegmentTree<int> t;
    for (int i=0; i<10; ++i)
        t.update(-100, -1, 1);

    cout << t.query(-100, -1);
}
*/

///* 只支持单点修改的动态开点线段树
template<typename T>
class AutoSegTree
{
public:
    static constexpr int MAXN = 1e6, L = -1e9-1, R = 1e9+1;

protected:
    int cnt = 1;
    struct node{
        int ls=0, rs=0;
        T value=0;
    } tree[MAXN]{};

    void _down(int i)
    {
        if (!tree[i].ls)
            tree[i].ls = ++cnt;
        if (!tree[i].rs)
            tree[i].rs = ++cnt;
    }

public:
    void plus(const int n, const T add, int i=1, int cl=L, int cr=R)
    {
        tree[i].value += add;
        if (cl==cr) return;
        _down(i);
        int mid = (cl+cr-1)/2;
        if (mid>=n)
            plus(n,add, tree[i].ls, cl, mid);
        else
            plus(n,add, tree[i].rs, mid+1, cr);
    }

    T query(int l, int r, int i=1, int cl=L, int cr=R)
    {
        if (l<=cl && cr<=r)
            return tree[i].value;
        _down(i);
        int mid = (cl+cr-1)/2;
        if (mid>=r)
            return query(l,r,tree[i].ls, cl, mid);
        else if (mid<l)
            return query(l,r,tree[i].rs, mid+1, cr);
        else
            return query(l,r,tree[i].ls, cl, mid)
                 + query(l,r,tree[i].rs, mid+1, cr);
    }

    T total() const
      { return tree[1].value; }
};

///* 权值线段树
template<typename T>
class wAutoSegTree
{
public:
    static constexpr int L = AutoSegTree<T>::L, R = AutoSegTree<T>::R;

    AutoSegTree<T> tree_;

    void insert(T n)
        { tree_.plus(n, 1); }

    void remove(T n)
        { tree_.plus(n, -1); }

    int count_pre(T n)
        { return tree_.query(L, n-1); }

    int count_suc(T n)
        { return tree_.query(n+1, R); }

    int rank(T n)
        { return count_pre(n)+1; }

    T pre(T n)
        { return nth(count_pre(n)); }

    T suc(T n)
        { return nth(tree_.total() - count_suc(n) + 1); }

    T nth(int n, int i=1, int cl=L, int cr=R)
    {
        auto &tree = tree_.tree;
        if (cl==cr)
            return cl;
        tree_._down(i);
        int mid = (cl+cr-1)/2;
        if (n<=tree[tree[i].ls].value)
            return nth(n, tree[i].ls, cl, mid);
        else
            return nth(n - tree[tree[i].ls].value, tree[i].rs, mid+1, cr);
    }
};