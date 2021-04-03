/**
 * File              : heuristics.cpp
 * Author            : Rustam Khafizov <super.rustamm@gmail.com>
 * Date              : 03.04.2021 16:17
 * Last Modified Date: 03.04.2021 17:59
 * Last Modified By  : Rustam Khafizov <super.rustamm@gmail.com>
 */

#include <cstdint>

#include "state.hpp"

int64_t hamming(State *final_state, State *state)
{
    int64_t result{-1};

    for (uint64_t y{0}; y < final_state->pzl.size(); ++y)
        for (uint64_t x{0}; x < final_state->pzl[y].size(); ++x)
            if (state->pzl[y][x] != final_state->pzl[y][x])
                ++result;
    if (state->pzl[state->pzl.size() - 1][state->pzl.size() - 1] != 0)
        --result;
    return (result);
}
