#include<bits/stdc++.h>
#include"list.hpp"
#define _for(i,a,b) for(int i = a; i <= b; i++)
#define _rfor(i,a,b) for(int i=a; i>=b; i--)
using namespace std;
using namespace List;
int main()
{
    dllist<int> l;
    int n;
    cin>>n;
    _for(i,1,n)
    {
        int a;
        cin>>a;
        l.ins_back(a);
    }
    l.bubblesort();
    l.print();
    return 0;
}