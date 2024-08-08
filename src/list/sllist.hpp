/*链表*/
#include<stdio.h>
#include<algorithm>
#define _for(i,a,b) for(int i = a; i <= b; i++)
#define _rfor(i,a,b) for(int i=a; i>=b; i--)
using namespace std;
namespace List
{
    template <class Data>
    class sllist                                  //单向链表，左闭右开，最末项为(0，NULL)无效项
    {
        public:
            class Node                            //单链表结点
            {
                public:
                    Data value;
                    Node* next;
                    Node()
                    {
                        value = 0;
                        next = nullptr;
                    }
                    Node(Data val)
                    {
                        value = val;
                        next = nullptr;
                    }
                    Node(Data val, Node* nxt)
                    {
                        value = val;
                        next = nxt;
                    }
            };
            Node* head;
            int length;
            sllist()
            {
                length = 0;
                head = new Node(0, nullptr);
            }
            sllist(Data val)
            {
                this->length = 1;
                this->head = new Node(val, nullptr);
            }

            void ins_back(Data value)             //插入在末尾
            {
                insert(head,value);
                length++;
            }
            void ins_front(Data value){           //插入在某处之前
                head = new Node(value,head);
                length++;
            }
            void ins_after(Node* node, Data value)//插入在某处之后
            {
                node->next = new Node(value, node->next);
                length++;
            }
            
            void del_front()                      //从前面删除，未释放内存
            {
                if (length <= 1)
                    return;
                head = head->next;
                length--;
            }
            void del_back()                       //从后面删除，未释放内存
            {
                if (length <= 1)
                    return;
                Node* now = head;
                while (now->next->next != nullptr)
                    now = now->next;
                now->value = 0;
                now->next = nullptr;
                length--;
            }
            void del_after(Node* node)            //从某位置后删除，未释放内存
            {
                node->next = node->next->next;
                length--;
            }
            
            void mov_after(Node* node)            //与后方元素交换（只交换值）
            {
                swap(node->value, node->next->value);
            }
            
            Node* find(Data value)                //查找某值
            {
                return find(head,value);
            }
            
            Node* getpos(int num)                 //获取第num项的指针
            {
                return getpos(num, head);
            }
            int getval(int num)                   //获取第num项的值
            {
                return getval(num, head);
            }
            
            Node* operator [](int num)            //获取第num项的值
            {
                return getpos(num);
            }
            
            void print()                          //输出链表，顶层print 
            {
                print(head);
                printf("\n");
            }
            void selectsort()                     //选择排序，O(n^2)
            {
                bool flag = true;
                while (flag)
                {
                    flag = false;
                    for(Node* node = head; node->next->next != nullptr; node = node->next)
                        if(node->value > node->next->value)
                        {
                            this->mov_after(node);
                            flag = true;
                        }
                }
            }
        private:
            void insert(Node* now, Data value){   //插入，底层
                if(now->next != nullptr)
                    insert(now->next, value);
                else
                {
                    now->value = value;
                    now->next = new Node(0, nullptr);
                }
            }
            Node* find(Node* now, Data value)     //查找，底层
            {
                if (now == nullptr || now->value == value)
                    return now;
                else
                    return find(now->next, value);
            }
            int getval(int num, Node* node)       //获取第num项的值，底层
            {
                return getpos(num, node)->value;
            }
            Node* getpos(int num, Node* node)     //获取第num项的指针，底层
            {
                if(num == 1)
                    return node;
                else
                    return getpos(num - 1, node->next);
            }
            void print(Node* node)                //输出，底层
            {
                if(node->next != nullptr)
                {
                    printf("%d ",node->value);
                    print(node->next);
                }
            }
    };
}
