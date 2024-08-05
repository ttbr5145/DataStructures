#include<cstdio>
using namespace std;
namespace Tree
{
    template <class Data>
    class bitree
    {
    public:
        struct Node
        {
        public:
            Data value;
            Node *father, *lftchild, *rgtchild;
            bool _at;//0表示在左子树，否则在右子树
            int degree;
            Node()
            {
                father = lftchild = rgtchild = NULL;
                degree = 0;
            }
            Node(Data val)
            {
                value = val;
                father = lftchild = rgtchild = NULL;
                degree = 0;
            }
            Node(Data val, Node* fa)
            {
                value = val;
                father = fa;
                lftchild = rgtchild = NULL;
                degree = 0;
            }
            Node(Data val, Node* fa, Node* lft, Node* rgt)
            {
                value = val;
                father = fa, lftchild = lft, rgtchild = rgt;
                degree = 0;
            }
        };
        Node* root;
        bool insert_able(Node* fa) { return fa->degree < 2; }  //查询是否可以插入结点
        void insert_at(Node* fa, Data val)
        {
            if (fa->lftchild == NULL) fa->lftchild = new Node(val, fa);
            else                      fa->rgtchild = new Node(val, fa);
            fa->degree++;
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
            if (node==NULL)
            {
                printf("back to fa\n");
                return;
            }
            printf("%d at %ls\n", node->value, (node->_at ? "rht" : "lft") );
            print(node->lftchild);
            print(node->rgtchild);
        }
    };
}