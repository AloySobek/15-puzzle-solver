/**
 * File              : main.cpp
 * Author            : Rustam Khafizov <super.rustamm@gmail.com>
 * Date              : 28.03.2021 01:10
 * Last Modified Date: 02.04.2021 01:40
 * Last Modified By  : Rustam Khafizov <super.rustamm@gmail.com>
 */

#include <iostream>

#include "graph.hpp"
#include "queue.hpp"

int main()
{
    PriorityQueue<State> *queue{new PriorityQueue<State>()};

    queue->tree_print();

    return (0);
}
