/**
 * File              : main.cpp
 * Author            : Rustam Khafizov <super.rustamm@gmail.com>
 * Date              : 28.03.2021 01:10
 * Last Modified Date: 28.03.2021 16:47
 * Last Modified By  : Rustam Khafizov <super.rustamm@gmail.com>
 */

#include <iostream>
#include <cstdlib>

int main(int argc, char **argv)
{
    std::cout << "Hello test world!" << std::endl;

    std::cout << atoi(argv[1]) << std::endl;

    return (0);
}
