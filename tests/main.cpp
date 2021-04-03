/**
 * File              : main.cpp
 * Author            : Rustam Khafizov <super.rustamm@gmail.com>
 * Date              : 28.03.2021 01:10
 * Last Modified Date: 03.04.2021 17:45
 * Last Modified By  : Rustam Khafizov <super.rustamm@gmail.com>
 */

#include <iostream>

template <class Lambda>
void test(Lambda one)
{
    std::cout << "In test" << std::endl;

    one();
}


int main()
{
    std::cout << "In main" << std::endl;

    test([&]() { std::cout << "In one" << hello << std::endl; });
    
    return (0);
}
