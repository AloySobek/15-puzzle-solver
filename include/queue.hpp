/**
 * File              : queue.hpp
 * Author            : Rustam Khafizov <super.rustamm@gmail.com>
 * Date              : 31.03.2021 00:50
 * Last Modified Date: 10.04.2021 15:36
 * Last Modified By  : Rustam Khafizov <super.rustamm@gmail.com>
 */

#ifndef QUEUE_HPP
# define QUEUE_HPP

# include <functional>
# include <iostream>
# include <cstdint>
# include <vector>
# include <string>
# include <queue>

template <class T1>
class QueueNode
{
public:
    QueueNode *right{nullptr};
    QueueNode *left{nullptr};
    
    T1 *key;

    QueueNode(T1 *key) : key{key} {}
};

template <class T1>
class PriorityQueue
{
public:
    PriorityQueue() {}

    void push(T1 *key) { if (key) q_root = _push(q_root, key); }
    void pop()         { q_root = _pop(q_root); };

    T1 *top()             { QueueNode<T1> *tmp = _top(q_root); return tmp ? tmp->key : nullptr;};
    T1 *contains(T1 *key) { QueueNode<T1> *tmp = _contains(q_root, key); return tmp ? tmp->key : nullptr; }

    bool empty() { return (q_root ? false : true); }
    void print() { _print("", q_root, false); }
    
    QueueNode<T1> *q_root{nullptr};
private:

    int64_t _height(QueueNode<T1> *root);

    QueueNode<T1> *_left_rotation(QueueNode<T1> *root);
    QueueNode<T1> *_left_right_rotation(QueueNode<T1> *root);
    QueueNode<T1> *_right_rotation(QueueNode<T1> *root);
    QueueNode<T1> *_right_left_rotation(QueueNode<T1> *root);

    QueueNode<T1> *_balance(QueueNode<T1> *root);
    QueueNode<T1> *_push(QueueNode<T1> *root, T1 *item);
    QueueNode<T1> *_pop(QueueNode<T1> *root);
    QueueNode<T1> *_top(QueueNode<T1> *root);

    QueueNode<T1> *_contains(QueueNode<T1> *root, T1 *key);
    void _print(const std::string &prefix, QueueNode<T1> *root, bool left);
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
        root = _balance(root);
    }
    else if (*(root->key) <= *item)
    {
        root->right = _push(root->right, item);
        root = _balance(root);
    }
    return (root);
}

template<class T1>
QueueNode<T1> *PriorityQueue<T1>::_pop(QueueNode<T1> *root)
{
    if (!root)
        return (nullptr);
    if (!root->left)
        return (root->right);
    root->left = _pop(root->left);
    return (_balance(root));
}

template<class T1>
QueueNode<T1> *PriorityQueue<T1>::_top(QueueNode<T1> *root)
{
    if (!root)
        return (nullptr);
    if (!root->left)
        return (root);
    return (_top(root->left));
}

template<class T1>
QueueNode<T1> *PriorityQueue<T1>::_contains(QueueNode<T1> *root, T1 *key)
{
    if (!root || !key)
        return (nullptr);
    if (*(root->key) == *key)
        return (root);
    if (*(root->key) > *key)
        return (_contains(root->left, key));
    return (_contains(root->right, key));
}

template<class T1>
void PriorityQueue<T1>::_print
    (const std::string &prefix, QueueNode<T1> *root, bool left)
{
    if (!root) return ;
    std::cout << prefix << (left ? "├──" : "└──" ) << *(root->key) << std::endl;
    _print(prefix + (left ? "│  " : "   "), root->left, true);
    _print(prefix + (left ? "│  " : "   "), root->right, false);
}

#endif
