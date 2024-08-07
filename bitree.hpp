#include<cstdio>
using namespace std;
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
                father = lftchild = rgtchild = NULL;
            }
            Node(Data val)
            {
                value = val;
                father = lftchild = rgtchild = NULL;
            }
            Node(Data val, Node* fa)
            {
                value = val;
                father = fa;
                lftchild = rgtchild = NULL;
            }
            Node(Data val, Node* fa, Node* lft, Node* rgt)
            {
                value = val;
                father = fa, lftchild = lft, rgtchild = rgt;
            }
        };
        Node* root;
        
        bitree() { root = NULL; }
        bool insert_able(Node* fa) { return fa->degree() < 2; }  //查询是否可以插入结点
        void insert_at(Node* fa, Data val)
        {
            if (fa->lftchild == NULL) fa->lftchild = new Node(val, fa);
            else                      fa->rgtchild = new Node(val, fa);
        }
        void del_at(Node* root)
        {
            if (root == NULL) return;
            if (root->lftchild != NULL) del(root->lftchild);
            if (root->rgtchild != NULL) del(root->rgtchild);
            if (root->_at) root->father->rhtchild = NULL;
            else           root->father->lftchild = NULL;
            delete root;
        }
        void print() { print(root); }         //中序遍历输出
    private:
        void print(Node* node)
        {
            if (node==NULL) return;
            printf("%d at %s\n", node->value, (node->_at ? "rht" : "lft") );
            print(node->lftchild);
            print(node->rgtchild);
            printf("back to fa\n");
        }
    };
}