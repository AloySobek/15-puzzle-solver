/**
 * File              : queue.hpp
 * Author            : Rustam Khafizov <super.rustamm@gmail.com>
 * Date              : 31.03.2021 00:50
 * Last Modified Date: 31.03.2021 01:30
 * Last Modified By  : Rustam Khafizov <super.rustamm@gmail.com>
 */

#ifndef QUEUE_HPP
# define QUEUE_HPP

# include <cstdint>
# include <iostream>
# include <string>

template <class T1>
class QueueNode
{
public:
    QueueNode *parent{nullptr};
    QueueNode *right{nullptr};
    QueueNode *left{nullptr};
    T1        key;

    QueueNode(T1 key) : key{key} {}
};


template <class T1>
class PriorityQueue
{
public:
    PriorityQueue() {}

    void               tree_print() { _tree_print("", q_root, false); }
    void               print()      { _print(q_root); std::cout << std::endl ;}
    PriorityQueue<T1> *push(T1 i)   { q_root = insert(q_root, i); return (this); }
    PriorityQueue<T1> *pop()        { delete_least(q_root); return (this); }
    T1                 top()        { return (delete_least(q_root, true)->key); }

private:
    QueueNode<T1> *q_root{nullptr};

    void _print(QueueNode<T1> *root)
    {
        if (!root)
            return ;
        _print(root->left);
        std::cout << root->key << " ";
        _print(root->right);
    }

    void _tree_print(const std::string &prefix, QueueNode<T1> *root, bool left)
    {
        if (!root)
            return ;
        std::cout << prefix << (left ? "├──" : "└──" ) << root->key << std::endl;
        _tree_print(prefix + (left ? "│  " : "   "), root->left, true);
        _tree_print(prefix + (left ? "│  " : "   "), root->right, false);
    }

    int64_t height(QueueNode<T1> *root)
    {
        return (root ? std::max(height(root->left), height(root->right)) + 1 : 0);
    }

    int64_t diff(QueueNode<T1> *root)
    {
        return (height(root->left) - height(root->right));
    }

    QueueNode<T1> *balance(QueueNode<T1> *root)
    {
        int64_t b_factor = diff(root);
        if (b_factor > 1)
        {
            // Stub
        }
    }

    QueueNode<T1> *insert(QueueNode<T1> *root, T1 item)
    {
        if (!root)
            return (new QueueNode<T1>(item));
        else if (root->key > item)
        {
            root->left = insert(root->left, item);
            root = balance(root);
        }
        else if (root->key <= item)
        {
            root->right = insert(root->right, item);
            root = balance(root);
        }
        return (root);
    }

    QueueNode<T1> *delete_least(QueueNode<T1> *root, bool back = false)
    {
        if (!root)
            return nullptr;
        delete_least(root->left);
        root->parent->left = root->right;
        if (back)
            return root;
        else
        {
            delete root;
            return nullptr;
        }
    }
};

#endif
