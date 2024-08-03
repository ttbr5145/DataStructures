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
    //用于生成随机数
	default_random_engine rd;
    bernoulli_distribution dist(0.5);// 生成1的概率为0.5
    const int MAXN = 20010;

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
            Node *head[MAXN], *tail[MAXN];
            int length;
            int maxlevel;

            skiplist()
            {
                length = 0;
                maxlevel = 0;
                _for(i, 0, MAXN)
                {
                    head[i] = new Node(0);
                    tail[i] = new Node(0);
                    head[i]->next = tail[i];
                    tail[i]->prev = head[i];
                }

                //初始化随机数
                rd.seed(time(0));
            }
            /*skiplist(Data val)
            {
                length = 1;
                maxlevel = 0;
                _for(i, 0, MAXN)
                {
                    head[i] = new Node(0)
                    tail[i] = new Node(0);
                    head[i]->next = tail[i];
                    tail[i]->prev = head[i];
                }
                head[0]->next = new Node(val);
                head[0]->next->next = tail[0], tail[0]->prev = head[0]->next;
                head[0]->next->prev = head[0];

                //初始化随机数
                rd.seed(time(0));
            }*/

            int randlevel()//获取随机层数
            {
                return randlevel(0);
            }

            void insert(Data val)//插入数据
            {
                int newlevel = randlevel();
                if (newlevel > maxlevel)
                {
                    newlevel = maxlevel + 1;
                    head[maxlevel + 1]->child = head[maxlevel];
                    head[maxlevel]->father = head[maxlevel + 1];
                    tail[maxlevel +1]->child = tail[maxlevel];
                    tail[maxlevel]->father = tail[maxlevel];
                    maxlevel++;
                }
                insert(newlevel, NULL, head[newlevel], tail[newlevel], val);
            }
            Node* find(Data val)//搜索数据（最高层）
            {
                return find(maxlevel, head[maxlevel], tail[maxlevel], val);
            }
            void del(Data val);
            
            void print()
            {
                int nowlevel = maxlevel;
                for (Node* start = head[maxlevel]; start != NULL; start = start->child, nowlevel--)
                {
                    printf("level %d: ", nowlevel);
                    for (Node* p = start->next; p->next != NULL; p = p->next)
                        printf("%d ",p->value);
                    printf("\n");
                }
            }
        private:
            bool rand()//随机生成0或1
            {
                return dist(rd);
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
            
            Node* insert(int level, Node* fa, Node* head, Node* tail, Data val)
            {
                Node *left = head, *right = tail;
                while (left->value < val) left = left->next;
                while (right->value > val) right = right->prev;
                if (left->next == right)
                {
                    Node *node = left->next = new Node(val, left->child, right->child, fa, NULL);
                    right->prev = node;
                    if (level > 0)
                        node->child = insert(level - 1, node, left, right, val);
                    else
                        node->child = NULL;
                    return node;
                }
                else//左右指针重合，均指在val处
                {
                    //left->times++;
                    insert(level - 1, left, left, right, val);
                    return left;
                }
            }
            Node* find(int level, Node* head, Node* tail, int val)
            {
                Node *left = head, *right = tail;
                while (left->value < val) left = left->next;
                while (right->value > val) right = right->prev;
                if (left->next == right)
                {
                    if(level > 0)
                        return find(level - 1, left->child, right->child);
                    else
                        return NULL;
                }
                else
                {
                    return left;
                }
            }
            void mov_after(Node* node);
            void mov_before(Node* node);
    };
}