/**
 * File              : edge.hpp
 * Author            : Rustam Khafizov <super.rustamm@gmail.com>
 * Date              : 27.03.2021 23:41
 * Last Modified Date: 28.03.2021 00:12
 * Last Modified By  : Rustam Khafizov <super.rustamm@gmail.com>
 */

#ifndef EDGE_HPP
# define EDGE_HPP

# include <cstdint>

class Node;

class Edge
{
public:
    int32_t cost;
    Node    *endpoint;

    Edge() {}
};

#endif
