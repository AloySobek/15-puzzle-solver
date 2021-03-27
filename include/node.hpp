/**
 * File              : node.hpp
 * Author            : Rustam Khafizov <super.rustamm@gmail.com>
 * Date              : 23.03.2021
 * Last Modified Date: 28.03.2021 00:01
 * Last Modified By  : Rustam Khafizov <super.rustamm@gmail.com>
 */

#ifndef NODE_HPP
# define NODE_HPP

#include <vector>
#include <cstdint>

class Edge;

template <class T1>
class Node
{
public:
    std::vector<Edge *> edges;
    T1 content;

    Node(T1 content) : content{content} {}
};

#endif
