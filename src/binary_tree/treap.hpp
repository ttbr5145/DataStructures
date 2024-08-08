#include<random>
#include"stree.hpp"
using namespace Tree;

namespace Tree
{
    const int MAXN = 20010;
    //用于生成随机数
	default_random_engine rd;
    uniform_int_distribution<int> dist(0, MAXN);

    template <class Data>
    class Info
    {
    public:
        using Type = Info<Data>;
        Data val;
        int pri;
        friend bool operator < (Type a, Type b) { return a.val < b.val; }
        friend bool operator > (Type a, Type b) { return a.val > b.val; }
        friend bool operator < (Type a, int b) { return a.val < b; }
        friend bool operator > (Type a, int b) { return a.val > b; }
    };

    template <class Data>
    class treap : public stree<Info<Data>>
    {
    public:

        using Type = Info<Data>;
        using Node = typename stree<Type>::Node;
        
        treap() { rd.seed(time(0));/*初始化随机数*/ }

        void insert(Data val)
        {
            Node* null = nullptr;
            insert(null, this->root, {val, dist(rd)}, 0);
        }
        void print() { print(this->root); }         //中序遍历输出
    private:
        void insert(Node *&fa, Node *&node, Type val, bool _at)       //递归插入结点
        {
            if (!node)
            {
                node = new Node(val, fa);
                node->_at = _at;
                rot(fa, node);
                return;
            }
            if (node->value < val)
                insert(node, node->rgtchild, val, 1);
            else
                insert(node, node->lftchild, val, 0);
        }
        void rot(Node *&fa, Node *&node)            //通过旋转调整Treap
        {
            if (!fa) return;

            if (fa->value.pri > node->value.pri)
            {
                Node* root = fa;
                if (node->_at) this->dex_rot(fa);
                else           this->lev_rot(fa);

                rot(fa->father, fa);
            }
        }
        
        void print(Node* node)
        {
            if (!node)
                return;
            printf("%d (%d) at %s\n", node->value.val, node->value.pri, (node->_at ? "rht" : "lft") );
            print(node->lftchild);
            print(node->rgtchild);
            printf("back to fa\n");
        }
    };
}