/**
 * File              : solver.hpp
 * Author            : Rustam Khafizov <super.rustamm@gmail.com>
 * Date              : 25.03.2021 13:34
 * Last Modified Date: 03.04.2021 17:59
 * Last Modified By  : Rustam Khafizov <super.rustamm@gmail.com>
 */

#ifndef SOLVER_HPP
# define SOLVER_HPP

# include <algorithm>
# include <iostream>
# include <cstdint>
# include <string>
# include <cmath>
# include <map>

# include "state.hpp"
# include "queue.hpp"
# include "heuristics.hpp"

class Solver
{
public:
    Solver() { heuristics["hamming"] = hamming; }

    bool is_solvable(State *initial_state);
    void solve(State *final_state, State *initial_state, const std::string &heuristic);
    
private:
    std::map<std::string, int64_t (*)(State *, State *)> heuristics;

    PriorityQueue<State> opened;
    PriorityQueue<State> closed;

    State *_up_move(State *final_state, State *state, const std::string &heuristic);
    State *_down_move(State *final_state, State *state, const std::string &heuristic);
    State *_right_move(State *final_state, State *state, const std::string &heuristic);
    State *_left_move(State *final_state, State *state, const std::string &heuristic);
    
    int64_t _get_inversion_count(std::vector<std::vector<int64_t>> &puzzle);
    int64_t _find_zero(std::vector<std::vector<int64_t>> &puzzle);
    
};

#endif
