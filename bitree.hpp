#include<cstdio>
using namespace std;
#ifdef NULL
#undef NULL
#endif
#define NULL nullptr

namespace Tree
{
    template <class Data>
    class bitree
    {
    public:
        class Node
        {
        public:
            Data value;
            Node *father, *lftchild, *rgtchild;
            bool _at;//0表示在左子树，否则在右子树
            int degree() { return (lftchild != nullptr) + (rgtchild != nullptr); }
            Node()
            {
                father = lftchild = rgtchild = nullptr;
            }
            Node(Data val)
            {
                value = val;
                father = lftchild = rgtchild = nullptr;
            }
            Node(Data val, Node* fa)
            {
                value = val;
                father = fa;
                lftchild = rgtchild = nullptr;
            }
            Node(Data val, Node* fa, Node* lft, Node* rgt)
            {
                value = val;
                father = fa, lftchild = lft, rgtchild = rgt;
            }
        };
        Node* root;
        
        bitree() { root = nullptr; }
        bool insert_able(Node* fa) { return fa->degree() < 2; }  //查询是否可以插入结点
        void insert_at(Node* fa, Data val)
        {
            if (fa->lftchild == nullptr) fa->lftchild = new Node(val, fa);
            else                      fa->rgtchild = new Node(val, fa);
        }
        void del_at(Node* root)
        {
            if (root == nullptr) return;
            if (root->lftchild != nullptr) del(root->lftchild);
            if (root->rgtchild != nullptr) del(root->rgtchild);
            if (root->_at) root->father->rhtchild = nullptr;
            else           root->father->lftchild = nullptr;
            delete root;
        }
        void print() { print(root); }         //中序遍历输出
    private:
        void print(Node* node)
        {
            if (node==nullptr) return;
            printf("%d at %s\n", node->value, (node->_at ? "rht" : "lft") );
            print(node->lftchild);
            print(node->rgtchild);
            printf("back to fa\n");
        }
    };
}