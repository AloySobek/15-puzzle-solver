/**
 * File              : main.cpp
 * Author            : Rustam Khafizov <super.rustamm@gmail.com>
 * Date              : 28.03.2021 01:10
 * Last Modified Date: 31.03.2021 23:18
 * Last Modified By  : Rustam Khafizov <super.rustamm@gmail.com>
 */

#include <iostream>

#include "queue.hpp"

int main()
{
    PriorityQueue<int> *queue{new PriorityQueue<int>()};

    queue->push(10)->push(1)->push(3)->push(2)->push(7)->push(5)->push(4);

    queue->tree_print();

    queue->pop();
    queue->tree_print();

    queue->push(1);
    queue->tree_print();

    /* queue->pop(); */
    /* queue->tree_print(); */

    /* queue->pop(); */
    /* queue->tree_print(); */

    /* queue->pop(); */
    /* queue->tree_print(); */

    /* queue->pop(); */
    /* queue->tree_print(); */

    /* queue->pop(); */
    /* queue->tree_print(); */

    /* queue->push(77); */
    /* queue->tree_print(); */

    return (0);
}
