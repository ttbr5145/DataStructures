
#include <iostream>
#include <cstdio>

#include "Trie.hpp"

class Trie_AC: public Trie<char>
{
public:
    int nxt[MAXN]{};

    void init_nxt()
    {
        for (int i=0; i<26; ++i)
            tree[0][i] = 1;

        int u, queue[MAXN];
        queue[1] = 1, nxt[1] = 0;

        for (int q1=1, end=1; q1<=end; ++q1)
        {
            u = queue[q1];
            for (int i=0; i<26; ++i)
                if (!tree[u][i])
                    tree[u][i] = tree[nxt[u]][i];   // 优化
                else{
                    queue[++end] = tree[u][i];
                    // int v = nxt[u];
                    // while (v && !tree[v][i])
                    //     v = nxt[v];
                    nxt[tree[u][i]] = tree[nxt[u]][i];
                }
        }
    }

    int AC_auto(const char *s)  // 一次性函数
    {
        int cnt=0, u=1, c, k;
        for (; *s; ++s)
        {
            c = *s - 'a';
            // 计数出现的单词
            k = tree[u][c];
            while (k > 1)
            {
                cnt += word[k];
                word[k] = 0; // 不重复计数
                k = nxt[k];
            }
            u = tree[u][c];
        }
        return cnt;
    }
};

int main()
{
    int n;
    char s[100];
    Trie_AC trac;
    scanf("%d", &n);
    do {
        scanf("%s", s);
        trac.insert(s);
    } while (--n);
    trac.init_nxt();
    scanf("%s", s);
    printf("%d", trac.AC_auto(s));
}