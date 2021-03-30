/**
 * File              : graph.hpp
 * Author            : Rustam Khafizov <super.rustamm@gmail.com>
 * Date              : 29.03.2021 00:27
 * Last Modified Date: 30.03.2021 18:34
 * Last Modified By  : Rustam Khafizov <super.rustamm@gmail.com>
 */

#ifndef GRAPH_HPP
# define GRAPH_HPP

# include <vector>
# include <cstdint>

class State
{
public:
    struct empty_tile
    {
        int32_t x;
        int32_t y;
    };
    std::vector<std::vector<int32_t>> puzzle;
    empty_tile crd;
    int32_t g;
    int32_t h;
    int32_t f;

    State(std::vector<std::vector<int32_t>> &puzzle) : puzzle{puzzle} {}
};

class NodeBase
{
public:
    class EdgeBase
    {
        NodeBase *endpoint;
    };
    NodeBase *parent;
};

template <class T1, class T2>
class Node : public NodeBase
{
public:
    class Edge : public NodeBase::EdgeBase
    {
    public:
        T2              *content;
        
        Edge(T2 *content) : content{content} {}
        ~Edge() { delete content; }
    };
    std::vector<Edge *> edges;
    T1                  *content;

    Node(T1 *content) : content{content} {}

    void connect(NodeBase *node, T2 *content)
    {
        node->parent = this;
        edges.push_back(new Node<T1, T2>::Edge(content));
    }

    ~Node() { delete content; }
};

#endif
