
#include <iostream>
#include <cstdio>

const int MAXN = 100;

class Trie_base
{
    int tot=1;
};

template<typename Type>
class Trie;

template<>
class Trie<char>
{
public:
    int tot=1;          // 1为根
    int tree[MAXN+2][26]{};
    int word[MAXN+2]{};

    int insert(const char *s)    // 默认全是小写字母
    {
        int u=1;
        for (; *s!='\0'; ++s)
        {
            int c = *s-'a';
            if (!tree[u][c])
                tree[u][c] = ++tot;
            u = tree[u][c];
        }
        return ++word[u];
    }

    bool find_word(const char *s) const
    {
        int u=1;
        for (; *s!='\0'; ++s)
        {
            int c = *s-'a';
            if (!tree[u][c])
                return false;
            u = tree[u][c];
        }
        return word[u];
    }

    bool find_prefix(const char *s) const
    {
        int u=1;
        for (; *s!='\0'; ++s)
        {
            int c = *s-'a';
            if (!tree[u][c])
                return false;
            u = tree[u][c];
        }
        return true;
    }
};

template<>
class Trie<int>
{
public:
    int tot=1;          // 1为根
    int tree[(MAXN+2)<<5][2]{};
    bool is_word[(MAXN+2)<<5]{};

    // 将自然数转换为二进制形式，从高位至低位插入
    void insert(int n)
    {
        int u=1;
        for (int i=1<<30; i; i>>=1)
        {
            bool c = n&i;
            if (!tree[u][c])
                tree[u][c] = ++tot;
            u = tree[u][c];
        }
        is_word[u] = true;
    }
};
