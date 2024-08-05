#include<bits/stdc++.h>
#define _for(i,a,b) for(int i = a; i <= b; i++)
#define _rfor(i,a,b) for(int i=a; i>=b; i--)
using namespace std;



#include"stree.hpp"
using namespace Tree;

int main()
{
    stree<int> stree;
    _for(i,1,10)
    {
        stree.insert(i);
    }
    stree.print();
    return 0;
}