#include<bits/stdc++.h>
#define _for(i,a,b) for(int i = a; i <= b; i++)
#define _rfor(i,a,b) for(int i=a; i>=b; i--)
using namespace std;

#include"stree.hpp"
using namespace Tree;

int main()
{
    printf("Hello\n");
    stree<int> stree;
    printf("Hello\n");
    _for(i,1,10)
    {
        stree.insert(i);
    }
    printf("Hello\n");
    stree.print();
    printf("Hello\n");
    return 0;
}