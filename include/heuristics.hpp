/**
 * File              : heuristics.hpp
 * Author            : Rustam Khafizov <super.rustamm@gmail.com>
 * Date              : 03.04.2021 16:18
 * Last Modified Date: 03.04.2021 17:40
 * Last Modified By  : Rustam Khafizov <super.rustamm@gmail.com>
 */

#ifndef HEURISTICS_HPP
# define HEURISTICS_HPP

# include <cstdint>
# include "state.hpp"

int64_t hamming(State *f_state, State *state);

#endif
