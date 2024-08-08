#include<bits/stdc++.h>
#define _for(i,a,b) for(int i = a; i <= b; i++)
#define _rfor(i,a,b) for(int i = a; i >= b; i--)
using namespace std;

#include"treap.hpp"
using namespace Tree;

int main()
{
    
	default_random_engine rd;
    uniform_int_distribution<int> dist(0, MAXN);// 生成随机数
    
    //初始化随机数
    rd.seed(time(0));

    _for(i,1,10) cout<<dist(rd)<<' ';
    cout<<endl;


    treap<int> treap;
    int a[] = {5,2,4,3,1,7,6,9,8,10};
    _for(i,0,9) treap.insert(a[i]);
    treap.print();
    // treap.dex_rot(treap.root);
    // printf("\n\n");
    // treap.print();
    // treap.lev_rot(treap.root);
    // treap.lev_rot(treap.root->rgtchild);
    // printf("\n\n");
    // treap.print();
    return 0;
}