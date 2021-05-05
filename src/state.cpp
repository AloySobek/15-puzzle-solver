/**
 * File              : state.cpp
 * Author            : Rustam Khafizov <super.rustamm@gmail.com>
 * Date              : 03.05.2021 19:25
 * Last Modified Date: 05.05.2021 16:07
 * Last Modified By  : Rustam Khafizov <super.rustamm@gmail.com>
 */

#include "state.hpp"

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
