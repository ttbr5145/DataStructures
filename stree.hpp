#include "bitree.hpp"
using namespace Tree;

namespace Tree
{
    template <class Data>
    class stree : public bitree<Data>
    { // 怎么run起来的
    using Node = typename bitree<Data>::Node;
    public:
        void insert(Data val) { insert(nullptr, this->root, val); }

    private:
        void insert(Node *fa, Node *node, Data val)
        {
            if (node == NULL)
            {
                node = new Node(val, fa);
                return;
            }
            if (node->value < val)
                insert(node, node->rgtchild, val);
            else
                insert(node, node->lftchild, val);
        }
    };
}