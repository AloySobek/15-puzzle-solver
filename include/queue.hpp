/**
 * File              : queue.hpp
 * Author            : Rustam Khafizov <super.rustamm@gmail.com>
 * Date              : 31.03.2021 00:50
 * Last Modified Date: 02.04.2021 01:36
 * Last Modified By  : Rustam Khafizov <super.rustamm@gmail.com>
 */

#ifndef QUEUE_HPP
# define QUEUE_HPP

# include <iostream>
# include <cstdint>
# include <string>

template <class T1>
class QueueNode
{
public:
    QueueNode *parent{nullptr};
    QueueNode *right {nullptr};
    QueueNode *left  {nullptr};
    
    T1 *key;

    QueueNode(T1 *key) : key{key} {}
};

template <class T1>
class PriorityQueue
{
public:
    PriorityQueue() {}

    PriorityQueue<T1> *push(T1 *key)
    {
        if (key) q_root = _push(q_root, key);
        return (this);
    }
    T1 *pop()
    {
        return(_pop(q_root)->key);
    }

    bool empty()           { return (q_root ? false : true); }
    bool contains(T1 *key) { return _contains(q_root, key); }
    void tree_print()      { _tree_print("", q_root, false); }
    
private:
    QueueNode<T1> *q_root{nullptr};

    int64_t _height(QueueNode<T1> *root);

    QueueNode<T1> *_left_rotation(QueueNode<T1> *root);
    QueueNode<T1> *_left_right_rotation(QueueNode<T1> *root);
    QueueNode<T1> *_right_rotation(QueueNode<T1> *root);
    QueueNode<T1> *_right_left_rotation(QueueNode<T1> *root);

    QueueNode<T1> *_balance(QueueNode<T1> *root);
    QueueNode<T1> *_push(QueueNode<T1> *root, T1 *item);
    QueueNode<T1> *_pop(QueueNode<T1> *root);

    bool _contains(QueueNode<T1> *root, T1 *key);
    void _tree_print(const std::string &prefix, QueueNode<T1> *root, bool left);
};

template<class T1>
int64_t PriorityQueue<T1>::_height(QueueNode<T1> *root)
{
    return (root ? std::max(_height(root->left), _height(root->right)) + 1 : -1);
}

template<class T1>
QueueNode<T1> *PriorityQueue<T1>::_left_rotation(QueueNode<T1> *root)
{
    QueueNode<T1> *tmp;

    root->parent = root->right;
    root->right->parent = root->parent;

    tmp = root->right;
    root->right = tmp->left;
    tmp->left = root;
    return (tmp);
}

template<class T1>
QueueNode<T1> *PriorityQueue<T1>::_left_right_rotation(QueueNode<T1> *root)
{
    root->left = _left_rotation(root->left);
    return (_right_rotation(root));
}

template<class T1>
QueueNode<T1> *PriorityQueue<T1>::_right_rotation(QueueNode<T1> *root)
{
    QueueNode<T1> *tmp;

    root->parent = root->left;
    root->left->parent = root->parent;

    tmp = root->left;
    root->left = tmp->right;
    tmp->right = root;
    return (tmp);
}

template<class T1>
QueueNode<T1> *PriorityQueue<T1>::_right_left_rotation(QueueNode<T1> *root)
{
    root->right = _right_rotation(root->right);
    return (_left_rotation(root));
}

template<class T1>
QueueNode<T1> *PriorityQueue<T1>::_balance(QueueNode<T1> *root)
{
    int64_t b_factor = _height(root->left) - _height(root->right); 
    if (b_factor > 1)
    {
        if (root->left && _height(root->left->left) - _height(root->left->right) < 0)
            root = _left_right_rotation(root);
        else
            root = _right_rotation(root);
    }
    else if (b_factor < -1)
    {
        if (root->right && _height(root->right->left) - _height(root->right->right) > 0)
            root = _right_left_rotation(root);
        else
            root = _left_rotation(root);
    }
    return (root);
}

template<class T1>
QueueNode<T1> *PriorityQueue<T1>::_push(QueueNode<T1> *root, T1 *item)
{
    if (!root)
        return (new QueueNode<T1>(item));
    else if (*(root->key) > *item)
    {
        root->left = _push(root->left, item);
        root->left->parent = root;
        root = _balance(root);
    }
    else if (*(root->key) <= *item)
    {
        root->right = _push(root->right, item);
        root->right->parent = root;
        root = _balance(root);
    }
    return (root);
}

template<class T1>
QueueNode<T1> *PriorityQueue<T1>::_pop(QueueNode<T1> *root)
{
    QueueNode<T1> *ghost{nullptr};

    if (!root)
        return nullptr;
    if (!(ghost = _pop(root->left)))
    {
        if (root->parent)
        {
            if (root->right)
            {
                root->right->parent = root->parent;
                root->parent->left = root->right;
            }
            else
                root->parent->left = nullptr;
        }
        else
            q_root = nullptr;
        ghost = root;
    }
    else
    {
        if (root == q_root)
            q_root = _balance(root);
        else
            _balance(root);
    }
    return (ghost);
}

template<class T1>
bool PriorityQueue<T1>::_contains(QueueNode<T1> *root, T1 *key)
{
    if (!root)
        return false;
    if (*(root->key) == *key)
        return true;
    if (*(root->key) > *key)
        return (_contains(root->left, key));
    return (_contains(root->right, key));
}

template<class T1>
void PriorityQueue<T1>::_tree_print
    (const std::string &prefix, QueueNode<T1> *root, bool left)
{
    if (!root)
        return ;
    std::cout << prefix << (left ? "├──" : "└──" ) << *(root->key) << std::endl;
    _tree_print(prefix + (left ? "│  " : "   "), root->left, true);
    _tree_print(prefix + (left ? "│  " : "   "), root->right, false);
}

#endif
