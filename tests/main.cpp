/**
 * File              : main.cpp
 * Author            : Rustam Khafizov <super.rustamm@gmail.com>
 * Date              : 28.03.2021 01:10
 * Last Modified Date: 11.04.2021 21:28
 * Last Modified By  : Rustam Khafizov <super.rustamm@gmail.com>
 */

#include <iostream>
#include <vector>

#include "queue.hpp"
#include "state.hpp"

int main()
{
    PriorityQueue<int64_t> test;

    test.push(new int64_t(6));

    test.push(new int64_t(7));
    test.push(new int64_t(8));
    test.push(new int64_t(7));
    test.push(new int64_t(8));

    test.print();
    std::cout << *(test.top()) << std::endl;
    test.print();
    test.pop();
    test.print();
    test.pop();

    test.push(new int64_t(10));
    test.push(new int64_t(10));
    test.push(new int64_t(10));
    test.push(new int64_t(10));
    test.push(new int64_t(10));
    test.push(new int64_t(10));
    test.push(new int64_t(10));
    test.push(new int64_t(10));

    test.pop();
    test.pop();
    test.pop();
    test.pop();
    test.pop();
    test.pop();
    test.pop();
    test.pop();
    test.pop();
    test.pop();
    test.pop();
    test.pop();
    test.pop();
    test.pop();

    test.print();

    test.push(new int64_t(6));
    test.push(new int64_t(8));
    test.push(new int64_t(7));

    test.pop();
    test.pop();

    test.print();

    return (0);
}
