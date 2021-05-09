/**
 * File              : state.cpp
 * Author            : Rustam Khafizov <super.rustamm@gmail.com>
 * Date              : 03.05.2021 19:25
 * Last Modified Date: 09.05.2021 00:49
 * Last Modified By  : Rustam Khafizov <super.rustamm@gmail.com>
 */

#include "state.hpp"
#include <string>
#include <algorithm>

State::State(State *other)
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

std::string& State::to_string()
{
    if (!key.empty())
        return key;
    std::string state_as_string("");

    for (uint64_t i{0}, size{pzl.size()}; i < size; ++i)
        state_as_string += std::to_string(pzl[i]) + " ";
    key = std::string(state_as_string);
    return (key);
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

bool State::is_ok() {
    std::vector<int64_t> ok(size * size);
    for (auto &item : ok)
        item = 0;
    for (const auto &item : pzl)
    {
        if (item < 0)
            return false;
        if ((uint64_t)item > size * size - 1)
            return false;
        ok[item] = 1;
    }
    return std::all_of(ok.cbegin(), ok.cend(), [](auto i){ return i != 0; });
}
