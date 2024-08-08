/*链表*/
#include<stdio.h>
#include<algorithm>
#define _for(i,a,b) for(int i = a; i <= b; i++)
#define _rfor(i,a,b) for(int i=a; i>=b; i--)
using namespace std;
namespace List
{
    template <class Data>
    class dllist           //双向链表
    {
        public:
            class Node
            {
                public:
                    Data value;
                    Node* prev;//此处有问题
                    Node* next;
                    Node()
                    {
                        value = 0;
                        prev = nullptr, next = nullptr;
                    }
                    Node(Data val)
                    {
                        value = val;
                        prev = nullptr, next = nullptr;
                    }
                    Node(Data val, Node* pre, Node* nxt)
                    {
                        value = val;
                        prev = pre, next = nxt;
                    }
            };
            Node* head;
			Node* tail;
            int length;
            dllist()
            {
                length = 0;
                tail = new Node(0, nullptr, nullptr);
                head = new Node(0, nullptr, tail);
                tail->prev = head;
            }
            dllist(Data val)
            {
                length = 1;
                head = new Node(0, nullptr, new Node(val, head, tail));
                tail = new Node(0, head->next, nullptr);
            }

            void ins_back(Data value)
            {
                insert(head, value);
                length++;
            }
            void ins_front(Data value)
            {
                head->next->prev = new Node(value, head, head->next);
                head->next = head->next->prev;
            }
            void ins_after(Data value, Node* node)
            {
                node->next->prev = new Node(value, node, node->next);
                node->next = node->next->prev;
            }
            void ins_before(Data value, Node* node)
            {
                node->prev->next = new Node(value, node->prev, node);
                node->prev = node->prev->next;
            }
            
            void del_after(Node* node)            //未清除内存
            {
                node->next->next->prev = node;
                node->next = node->next->next;
            }
            void del_before(Node* node)           //未清除内存
            {
                node->prev->prev->next = node;
                node->prev = node->prev->prev;
            }
            
            void mov_after(Node* node)
            {
                swap(node->value, node->next->value);
            }
            void mov_before(Node* node)
            {
                swap(node->value, node->prev->value);
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
            
            Data operator [](int num)
            {
                return getpos(num);
            }

            //待优化
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
            void print()                          //输出链表，顶层print 
            {
                print(head->next);
                printf("\n");
            }
        private:
            void insert(Node* now, Data value)
            {
                if (now->next != tail)
                    insert(now->next, value);
                else
                {
                    now->next = new Node(value, now, tail);
                    tail->prev = now->next;
                }
            }
            Node* find(Node* now, Data value)     //底层
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
            void print(Node* node)                //底层
            {
                if(node->next != nullptr)
                {
                    printf("%d ",node->value);
                    print(node->next);
                }
            }
    };
}
