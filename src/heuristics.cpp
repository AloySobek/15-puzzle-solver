/**
 * File              : heuristics.cpp
 * Author            : Rustam Khafizov <super.rustamm@gmail.com>
 * Date              : 03.04.2021 16:17
 * Last Modified Date: 10.04.2021 00:51
 * Last Modified By  : Rustam Khafizov <super.rustamm@gmail.com>
 */

#include <cstdint>
#include <cstdlib>

#include "state.hpp"

void hamming(const State *final, State *intermediate)
{
    intermediate->h = 0;

    for (uint64_t y{0}; y < final->pzl.size(); ++y)
        for (uint64_t x{0}; x < final->pzl[y].size(); ++x)
            if (intermediate->pzl[y][x] != 0 && intermediate->pzl[y][x] != final->pzl[y][x])
                ++(intermediate->h);
}

void manhattan(const State *final, State *intermediate)
{
    intermediate->h = 0;

    for (int64_t y{0}; y < (int64_t)final->pzl.size(); ++y)
        for (int64_t x{0}; x < (int64_t)final->pzl[y].size(); ++x)
            if (intermediate->pzl[y][x] != 0 && intermediate->pzl[y][x] != final->pzl[y][x])
                for (int64_t y2{0}; y2 < (int64_t)final->pzl.size(); ++y2)
                    for (int64_t x2{0}; x2 < (int64_t)final->pzl[y2].size(); ++x2) 
                        if (final->pzl[y2][x2] == intermediate->pzl[y][x])
                            intermediate->h += std::abs(std::max(x2, x) - std::min(x2, x))
                                + std::abs(std::max(y2, y) - std::min(y2, y));
}
