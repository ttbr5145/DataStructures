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
    auto result = sl.find(3);
    if (result != NULL)
    {
        if (result->next != NULL)
            printf("3 has found, and the next is %d (at level %d)\n", result->next->value, result->level);
        else
            printf("3 has found, but there's nothing at the next (at level %d)\n", result->level);
    }
    else
        cout<<"Can't find 3\n";
    return 0;
}