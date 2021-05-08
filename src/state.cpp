/**
 * File              : state.cpp
 * Author            : Rustam Khafizov <super.rustamm@gmail.com>
 * Date              : 03.05.2021 19:25
 * Last Modified Date: 09.05.2021 00:49
 * Last Modified By  : Rustam Khafizov <super.rustamm@gmail.com>
 */

#include "state.hpp"
#include <string>

State::State(const State *other)
{
    this->zero_position = other->zero_position;
    this->parent = other;
    this->size = other->size;
    this->pzl = other->pzl;
    this->g = other->g;
    this->h = other->h;
}

std::ostream &operator<<(std::ostream &os, const State &obj)
{
    std::cout << obj.g + obj.h;
    return (os);
}

std::string State::to_string() const
{
    std::string state_as_string("");

    for (uint64_t i{0}, size{pzl.size()}; i < size; ++i)
        state_as_string += std::to_string(pzl[i]) + " ";

    return (state_as_string);
}

std::string State::row_to_string(uint64_t n) const
{
    std::string row_state_as_string("");

    for (uint64_t i{size * n}; i < size * n + size; ++i)
        if (size > 3)
            row_state_as_string += std::to_string(pzl[i]) + (std::to_string(pzl[i]).size() > 1 ? " " : "  ");
        else
            row_state_as_string += std::to_string(pzl[i]) + " ";

    return (row_state_as_string);
}
