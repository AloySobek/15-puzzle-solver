/**
 * File              : heuristics.hpp
 * Author            : Rustam Khafizov <super.rustamm@gmail.com>
 * Date              : 03.04.2021 16:18
 * Last Modified Date: 10.04.2021 00:50
 * Last Modified By  : Rustam Khafizov <super.rustamm@gmail.com>
 */

#ifndef HEURISTICS_HPP
# define HEURISTICS_HPP

# include <cstdint>
# include "state.hpp"

void hamming(const State *final, State *intermediate);
void manhattan(const State *final, State *intermediate);

#endif
