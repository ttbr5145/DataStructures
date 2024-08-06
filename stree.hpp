#include "bitree.hpp"
using namespace Tree;

namespace Tree
{
    template <class Data>
    class stree : public bitree<Data>
    {
    using Node = typename bitree<Data>::Node;
    public:
        void insert(Data val) { insert(nullptr, this->root, val); }
        void trans_at(Node *&node, Node *&newfa)        //转移父亲
        {
            if (node->father != nullptr)
            {
                if (node->_at) node->father->rgtchild = nullptr;
                else           node->father->lftchild = nullptr;
            }
            node->father = fa;
            if (fa != nullptr)
            {
                if (fa->value > node->value)  fa->lftchild = node;
                else                          fa->rgtchild = node;
            }
        }
        void trans(Node *&node, Node*&root)             //转移父亲至可插点
        {
            if (root->insert_able())
            {
                trans(node, root);
                return;
            }
            if (node->value < root->value) trans(node, root->lftchild);
            else                           trans(node, root->rgtchild);
        }
        void swap(Node*&node1, Node*&node2)              //交换父亲
        {
            Node* temp;
            temp->father = node1->father;
            node1->father = node2->father;
            node2->father = temp->father;
            if(node1->_at) node1->father->rgtchild = node1;
            else           node1->father->lftchild = node1;
            if(node2->_at) node2->father->rgtchild = node2;
            else           node2->father->lftchild = node2;
        }
        void dex_rot()                       // 右旋
        {
            Node* ori_root = root, new_root = root_rgtchild, odd_node = root->rgtchild->lftchild;
            ori_root->rgtchild = odd_node, odd_node->father = ori_root, odd_node->_at = 1;
            new_root->lftchild = ori_root, ori_root->father = new_root, ori_root->_at = 0;
            new_root->father = nullptr, new_root->_at = 0;
        }
        void lev_rot()                      // 左旋（未完成）
        {
            Node* ori_root = root, new_root = root_rgtchild, odd_node = root->rgtchild->lftchild;

        }
    private:
        void insert(Node *fa, Node *&node, Data val) //插入
        {
            if (node == nullptr)
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