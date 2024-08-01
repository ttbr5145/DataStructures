#include<stdio.h>
#include<algorithm>
#include"dllist.hpp"
#define _for(i,a,b) for(int i = a; i <= b; i++)
#define _rfor(i,a,b) for(int i=a; i>=b; i--)
using namespace std;
using namespace List;
namespace List
{
    class skiplist : public dllist
    {
        public:
            class skipNode : public Node
            {
                public:
                    int level;
                    Node* child;
                    Node* father;
                    skipNode()
                    {
                        level = 0;
                        child = NULL, father = NULL;
                    }
            };
            int maxlevel;
            
            skiplist()
            {
                maxlevel = 0;
            }
    };
}