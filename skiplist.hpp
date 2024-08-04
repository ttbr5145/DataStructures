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
    const int MAXN = 20010, INF = 0x3f3f3f3f;

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
                _for(i, 0, MAXN - 1)
                {
                    head[i] = new Node(-INF);
                    tail[i] = new Node(INF);
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

            int randlevel()//获取随机层数，该值小于等于当前的maxlevel + 1
            {
                return randlevel(0);
            }

            void insert(Data val)//插入数据
            {
                int newlevel = randlevel();
                if (newlevel > maxlevel)  //动态初始化，初始化第 maxlevel + 1 层
                {
                    ++maxlevel;
                    head[maxlevel]->child = head[maxlevel - 1], head[maxlevel - 1]->father = head[maxlevel];
                    tail[maxlevel]->child = tail[maxlevel - 1], tail[maxlevel - 1]->father = tail[maxlevel];
                }

                insert(maxlevel, newlevel, NULL, head[maxlevel], tail[maxlevel], val);
            }

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
            int randlevel(int level)//获得随机层数，底层
            {
                if (level > maxlevel)
                    return level;
                else
                {
                    bool r = dist(rd);
                    if (r)
                        return randlevel(level + 1);
                    else
                        return level;
                }
            }
            
            Node* add(Node* left, Node* right, Node* father, Data val) // 在left和right之间插入一个结点，其父结点为fa
            {
                Node* node =
                left->next = new Node(val, left, right, father, NULL);
                right->prev = node;
                if (father != NULL) father->child = node;
                return node;
            }

            void insert(int nowlevel, int datalevel, Node* fa, Node* head, Node* tail, Data val)
            {
                printf("insert %d at level %d, now at level %d\n", val, datalevel, nowlevel);
                Node *left = head, *right = tail;
                while (left->next->value < val && left->next != right){printf("left goes once\n");left = left->next;}// printf("left end\n");
                while (right->prev->value > val && right->prev != left){printf("right goes once\n");right = right->prev;}// printf("right end\n");

                Node* tempfa;
                if (left->next == right)
                {
                    tempfa = NULL;                          //情况1，此level无数据，不在此level插入数据
                    if (nowlevel <= datalevel)
                        tempfa = add(left, right, fa, val); //情况2，此level无数据，在此level插入数据
                }
                else            //左右指针重合，均指在val处，说明此level已有数据
                {
                    // left->times++;
                    tempfa = left;                          //情况3，此level已有数据
                }

                if (nowlevel > 0)
                        insert(nowlevel - 1, datalevel, tempfa, left->child, right->child, val);
            }
    };
}