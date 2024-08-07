#include<bits/stdc++.h>
#define _for(i,a,b) for(int i = a; i <= b; i++)
#define _rfor(i,a,b) for(int i = a; i >= b; i--)
using namespace std;

#include"stree.hpp"
using namespace Tree;

int main()
{
    stree<int> stree;
    int a[] = {5,2,4,3,1,7,6,9,8,10};
    _for(i,0,9) stree.insert(a[i]);
    stree.print();
    stree.dex_rot();
    printf("\n\n");
    stree.print();
    stree.lev_rot();
    stree.lev_rot();
    printf("\n\n");
    stree.print();
    return 0;
}