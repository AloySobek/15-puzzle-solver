/**
 * File              : graph.hpp
 * Author            : Rustam Khafizov <super.rustamm@gmail.com>
 * Date              : 29.03.2021 00:27
 * Last Modified Date: 29.03.2021 00:39
 * Last Modified By  : Rustam Khafizov <super.rustamm@gmail.com>
 */

#ifndef GRAPH_HPP
# define GRAPH_HPP

# include <vector>
# include <cstdint>

class State
{
public:
    std::vector<std::vector<int32_t>> puzzle;
    int32_t g;
    int32_t h;
    int32_t f;
};


template <class T1, class T2>
class Node
{
public:
    class Edge
    {
    public:
        Node<T1, T2>    *endpoint;
        T2              wight;
        
        Edge() {}
    };
    std::vector<Edge *> edges;
    T1                  content;

    Node(T1 content) : content{content} {}
};

#endif
