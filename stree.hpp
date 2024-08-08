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
            Node *ori_root = root, *new_root = root->rgtchild, *odd_node = root->rgtchild->lftchild;
            ori_root->rgtchild = odd_node;
            if (odd_node) 
            {
                odd_node->father = ori_root;
                odd_node->_at = 1;
            }
            new_root->lftchild = ori_root, ori_root->father = new_root, ori_root->_at = 0;
            new_root->father = NULL, new_root->_at = 0;
            root = new_root;
        }
        void lev_rot(Node *&root)                       // 左旋
        {
            Node* ori_root = root, *new_root = root->lftchild, *odd_node = root->lftchild->rgtchild;
            ori_root->lftchild = odd_node;
            if (odd_node) 
            {
                odd_node->father = ori_root;
                odd_node->_at = 0;
            }
            new_root->rgtchild = ori_root, ori_root->father = new_root, ori_root->_at = 1;
            new_root->father = NULL, new_root->_at = 1;
            root = new_root;
        }

        void insert(Data val) { insert(NULL, this->root, val, 0); }
        /*
        void trans_at(Node *&node, Node *&newfa)        //转移父亲
        {
            if (node->father != NULL)
            {
                if (node->_at) node->father->rgtchild = NULL;
                else           node->father->lftchild = NULL;
            }
            node->father = newfa;
            if (newfa != NULL)
            {
                if (newfa->value > node->value)  newfa->lftchild = node;
                else                             newfa->rgtchild = node;
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
        */
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