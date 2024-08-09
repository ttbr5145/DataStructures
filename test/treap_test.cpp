#include<iostream>
#define _for(i,a,b) for(int i = a; i <= b; i++)
#define _rfor(i,a,b) for(int i = a; i >= b; i--)
using namespace std;

#include"../src/binary_tree/treap.hpp"
using namespace Tree;

int main()
{
    treap<int> treap;
    int a[] = {5,2,4,3,1,7,6,9,8,10};
    _for(i,0,9)
        treap.insert(a[i]);
    treap.print();
    if (treap.find(3)) cout<<"3 has been found.\n";
    else cout<<"can't find 3\n";
    treap.del(3);
    if (treap.find(3)) cout<<"3 has been found.\n";
    else cout<<"can't find 3\n";
    return 0;
}