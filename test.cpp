#include<bits/stdc++.h>
#include"skiplist.hpp"
#define _for(i,a,b) for(int i = a; i <= b; i++)
#define _rfor(i,a,b) for(int i=a; i>=b; i--)
using namespace std;
using namespace List;
int main()
{
    skiplist<int> sl;
    _for(i,1,10)
    {
        int a;
        cin>>a;
        sl.insert(a);
    }
    sl.print();
    return 0;
}