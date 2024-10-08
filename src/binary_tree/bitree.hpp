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
            Node *father = nullptr, *lftchild = nullptr, *rgtchild = nullptr;
            bool _at;//0表示在左子树，否则在右子树
            int degree() { return (lftchild != nullptr) + (rgtchild != nullptr); }

            Node() {}
            Node(Data val) : value(val)
            {}
            Node(Data val, Node* fa)
              : value(val), father(fa)
            {}
            Node(Data val, Node* fa, Node* lft, Node* rgt)
              : value(val), father(fa), lftchild(lft), rgtchild(rgt)
            {}
        };
        Node* root = nullptr;

        bool insert_able(Node* fa) { return fa->degree() < 2; }  //查询是否可以插入结点
        void insert(Node* fa, Data val)
        {
            if (!fa->lftchild)
                fa->lftchild = new Node(val, fa);
            else
                fa->rgtchild = new Node(val, fa);
        }
        void del_at(Node* root)
        {
            if (!root) return;
            if (root->lftchild)
                del_at(root->lftchild);
            if (root->rgtchild)
                del_at(root->rgtchild);
            if (root->_at)
                root->father->rgtchild = nullptr;
            else
                root->father->lftchild = nullptr;
            delete root;
        }
        
        void print() { print(root); }         //中序遍历输出
    private:
        void print(Node* node)
        {
            if (!node) return;
            printf("%d at %s\n", node->value, (node->_at ? "rht" : "lft") );
            print(node->lftchild);
            print(node->rgtchild);
            printf("back to fa\n");
        }
    };
}