#include<stdio.h>
#include<algorithm>

#include<random>
#include<ctime>

#include"dllist.hpp"
#define _for(i,a,b) for(int i = a; i <= b; i++)
#define _rfor(i,a,b) for(int i=a; i>=b; i--)
using namespace std;
using namespace List;
namespace List
{
    template <class Data>
    class skiplist
    {
        public:
            class Node
            {
                public:
                    Data value;
                    int level;
                    Node *prev, *next, *child, *father;
                    Node()
                    {
                        value = 0;
                        level = 0;
                        prev = NULL, next = NULL;
                        child = NULL, father = NULL;
                    }
                    Node(Data val)
                    {
                        value = val;
                        prev = next = child = father = NULL;
                    }
                    Node(Data val, Node* pre, Node* nxt, Node* chd, Node* fa)
                    {
                        value = val;
                        prev = pre, next = nxt, child = chd, father = fa;
                    }
            };
            Node *head;    //head永远为(0,NULL,next,NULL,NULL)
            int length;
            int maxlevel;

            //用于生成随机数
	        default_random_engine e;
            bernoulli_distribution u(0.5); // 生成1的概率为0.5
            skiplist()
            {
                length = 0;
                maxlevel = 0;
                head = new Node(0, NULL, NULL, NULL, NULL);

                //初始化随机数
                e.seed(time(0));
            }
            skiplist(Data val)
            {
                length = 1;
                maxlevel = 0;
                head = new Node(0, NULL, new Node(val), NULL, NULL);
                head->next->prev = head;

                //初始化随机数
                e.seed(time(0));
            }

            int randlevel()//获取随机层数
            {
                return randlevel(0);
            }
        private:
            bool rand()//随机生成0或1
            {
                return u(e);
            }
            int randlevel(int level)//获得随机层数，底层
            {
                if (level > maxlevel)
                    return level;
                else
                {
                    bool r = rand();
                    if (r)
                        return randlevel(level + 1);
                    else
                        return level;
                }
            }
            
    };
}