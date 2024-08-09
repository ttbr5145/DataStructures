
#include <iostream>
#include <cstring>

char s[]=".aab", target[]=".aab";
int n = strlen(s+1), m = strlen(target+1);
int p[100];

void pre()
{
    p[1] = 0;
    int j = 0;
    for (int i=1; i<m; ++i)
    {
        while (j>0 && target[j+1]!=target[i+1])
            j = p[j];
        if (target[j+1]==target[i+1])
            ++j;
        p[i+1] = j;
    }
}

int KMP(const char *s)
{
    int cnt=0, j=0;
    for (int i=0; i<n; ++i)
    {
        while (j>0 && target[j+1] != s[i+1])
            j = p[j];
        if (target[j+1] == s[i+1])
            ++j;
        if (j == m)
        {
            // std::cout << s[i+1-m+1+4]<<' '<<target[i+1-m+1+4]<<'\t';
            std::cout << i+1-m+1 <<std::endl;
            j=p[j];     // 不重叠改为0
            ++cnt;
        }
    }
    return cnt;
}

int main()
{
    pre();
    std::cout << KMP(s) << std::endl;
}