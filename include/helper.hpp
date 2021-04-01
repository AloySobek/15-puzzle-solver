/**
 * File              : helper.hpp
 * Author            : Rustam Khafizov <super.rustamm@gmail.com>
 * Date              : 01.04.2021 21:21
 * Last Modified Date: 02.04.2021 01:33
 * Last Modified By  : Rustam Khafizov <super.rustamm@gmail.com>
 */

#ifndef HELPER_HPP
#define HELPER_HPP

# include "graph.hpp"

class Helper
{
public:
    Helper() {}

    int64_t best_h(std::vector<State *> &states)
    {
        int64_t max{-1};

        for (State *state : states)
            if (state->g + state->h
            state->
    }
}

#endif
