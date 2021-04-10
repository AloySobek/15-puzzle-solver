/**
 * File              : state.cpp
 * Author            : Rustam Khafizov <super.rustamm@gmail.com>
 * Date              : 03.04.2021 18:00
 * Last Modified Date: 09.04.2021 13:40
 * Last Modified By  : Rustam Khafizov <super.rustamm@gmail.com>
 */

#include "state.hpp"

void State::print() const
{
    for (uint64_t y{0}; y < pzl.size(); ++y, std::cout << std::endl)
        for (uint64_t x{0}; x < pzl[y].size(); ++x)
            std::cout << pzl[y][x] << " ";
}
