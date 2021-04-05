/**
 * File              : main.cpp
 * Author            : Rustam Khafizov <super.rustamm@gmail.com>
 * Date              : 28.03.2021 01:10
 * Last Modified Date: 05.04.2021 15:59
 * Last Modified By  : Rustam Khafizov <super.rustamm@gmail.com>
 */

#include <iostream>
#include <vector>

#include "queue.hpp"

int main()
{
    /* std::vector<std::vector<int64_t>> test; */

    /* test = {{1, 2, 3}, {1, 2, 3}, {1, 2, 3}}; */

    /* for (std::vector<int64_t> &row : test) */
    /* { */
    /*     for (int64_t &i : row) */
    /*         std::cout << i << " "; */
    /*     std::cout << std::endl; */
    /* } */

    PriorityQueue<int64_t> test;

    test.push(new int64_t(6));
    test.push(new int64_t(7));
    test.push(new int64_t(8));

    test.tree_print();
    
    test.pop();

    test.tree_print();

    return (0);
}
