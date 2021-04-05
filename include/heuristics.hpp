/**
 * File              : heuristics.hpp
 * Author            : Rustam Khafizov <super.rustamm@gmail.com>
 * Date              : 03.04.2021 16:18
 * Last Modified Date: 05.04.2021 18:35
 * Last Modified By  : Rustam Khafizov <super.rustamm@gmail.com>
 */

#ifndef HEURISTICS_HPP
# define HEURISTICS_HPP

# include <cstdint>
# include "state.hpp"

int64_t hamming(State *final, State *intermediate);
int64_t manhattan(State *final, State *intermediate);

#endif
