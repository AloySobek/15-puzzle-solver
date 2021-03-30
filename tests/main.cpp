/**
 * File              : main.cpp
 * Author            : Rustam Khafizov <super.rustamm@gmail.com>
 * Date              : 28.03.2021 01:10
 * Last Modified Date: 31.03.2021 01:12
 * Last Modified By  : Rustam Khafizov <super.rustamm@gmail.com>
 */

#include <iostream>

#include "../include/queue.hpp"

int main(int argc, char **argv)
{
    PriorityQueue<int> *queue{new PriorityQueue<int>()};

    queue->push(10)->push(1)->push(3)->push(2)->push(7)->push(5);

    queue->print();
    queue->tree_print();

    return (0);
}
