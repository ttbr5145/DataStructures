#include "bitree.hpp"
using namespace Tree;

namespace Tree
{
    template <class Data>
    class stree : public bitree<Data>
    {
    public:
        using Node = typename bitree<Data>::Node;

        void dex_rot(Node *&root)                       // 右旋
        {
            if (!root || !root->rgtchild) return;
            Node *ori_root = root, *new_root = root->rgtchild,
            *odd_node = new_root->lftchild;

            ori_root->rgtchild = odd_node;
            if (odd_node) 
            {
                odd_node->father = ori_root;
                odd_node->_at = 1;
            }
            new_root->lftchild = ori_root, ori_root->father = new_root, ori_root->_at = 0;
            new_root->father = nullptr, new_root->_at = 0;
            root = new_root;
        }
        void lev_rot(Node *&root)                       // 左旋
        {
            if (!root || !root->lftchild) return;
            Node *ori_root = root, *new_root = root->lftchild,
            *odd_node = new_root->rgtchild;

            ori_root->lftchild = odd_node;
            if (odd_node) 
            {
                odd_node->father = ori_root;
                odd_node->_at = 0;
            }
            new_root->rgtchild = ori_root, ori_root->father = new_root, ori_root->_at = 1;
            new_root->father = nullptr, new_root->_at = 1;
            root = new_root;
        }

        void insert(Data val) { insert(nullptr, this->root, val, 0); }
    private:
        void insert(Node *fa, Node *&node, Data val, bool _at) //插入
        {
            if (!node)
            {
                node = new Node(val, fa);
                node->_at = _at;
                return;
            }
            if (node->value < val)
                insert(node, node->rgtchild, val, 1);
            else
                insert(node, node->lftchild, val, 0);
        }
    };
}