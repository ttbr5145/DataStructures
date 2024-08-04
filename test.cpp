#include<bits/stdc++.h>
#include"skiplist.hpp"
#define _for(i,a,b) for(int i = a; i <= b; i++)
#define _rfor(i,a,b) for(int i=a; i>=b; i--)
using namespace std;
using namespace List;
int main()
{
    skiplist<int> sl;
    int n;
    cin>>n;
    _for(i,1,n)
    {
        int data;
        cin>>data;
        sl.insert(data);
    }
    sl.print();
    return 0;
}