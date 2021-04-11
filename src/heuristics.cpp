/**
 * File              : heuristics.cpp
 * Author            : Rustam Khafizov <super.rustamm@gmail.com>
 * Date              : 03.04.2021 16:17
 * Last Modified Date: 11.04.2021 23:28
 * Last Modified By  : Rustam Khafizov <super.rustamm@gmail.com>
 */

#include <cstdint>
#include <cstdlib>

#include "state.hpp"

void hamming(const State *final, State *intermediate)
{
    intermediate->h = 0;

    for (uint64_t i{0}, size{final->pzl.size()}; i < size; ++i)
        if (intermediate->pzl[i] != 0 && intermediate->pzl[i] != final->pzl[i])
            ++(intermediate->h);
}

void manhattan(const State *final, State *intermediate)
{
    intermediate->h = 0;

    for (uint64_t i{0}, isize{final->pzl.size()}; i < isize; ++i)
        if (intermediate->pzl[i] != 0 && intermediate->pzl[i] != final->pzl[i])
            for (uint64_t j{0}, jsize{final->pzl.size()}; j < jsize; ++j)
                if (intermediate->pzl[j] == final->pzl[i])
                    intermediate->h += (std::max(i % final->n, j % final->n) -
                                        std::min(i % final->n, j % final->n)) +
                                       (std::max(i / final->n, j / final->n) -
                                        std::min(i / final->n, j / final->n));
}

void linear_conflicts(const State *final, State *intermediate)
{
    manhattan(final, intermediate);
}
