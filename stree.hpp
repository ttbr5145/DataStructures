#include"bitree.hpp"
using namespace Tree;

namespace Tree
{
    template <class Data>
    class stree : public bitree<Data>
    {
        public:
            void insert(Data val) { insert(NULL, root, val); }
        private:
            void insert(Node * fa, Node* node, Data val)
            {
                if (node == NULL)
                {
                    node = new Node(val, fa);
                    return;
                }
                if (node->this->value < val) insert(node, node->rhtchild, val);
                else                 insert(node, node->lftchild, val);
            }
    };
}