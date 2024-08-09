
constexpr int MAXN = 102;

template<class T>
constexpr T lowbit(T n)
    { return n&-n; }

template<class Type>
class BIT
{
protected:
    int size_;
    Type c_[MAXN]{};

public:
    BIT(int size)
        :size_(size){}

    void plus(int p, Type k)
    {
        for (; p<=size_; p+=lowbit(p))
            c_[p] += k;
    }

    Type sum(int x) const
    {
        Type s = 0;
        for (; x; x-=lowbit(x))
            s += c_[x];
        return s;
    }

    Type sum(int l, int r) const
      { return sum(r) - sum(l-1); }

// 以下代码仅供参考
    struct ref
    {
        BIT<Type> &_this;
        const int p;

        ref(BIT<Type> &a, const int &x)
            :_this(a), p(x){}
        void operator+=(const Type &k)
        {
            _this.plus(p, k);
        }
    };
    ref operator[](int p)
    {
        return ref(*this, p);
    }
//
};

/**
 @code
#include <iostream>
int main()
{
    using namespace std;

    int n;
    cin >> n;
    BIT<int> a(n);

    for (int x=1; x<=n; ++x)
        a[x] += x*x;

    cout << a.sum(n);
}
 @endcode
*/