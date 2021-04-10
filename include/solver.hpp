/** * File              : solver.hpp
 * Author            : Rustam Khafizov <super.rustamm@gmail.com>
 * Date              : 25.03.2021 13:34
 * Last Modified Date: 10.04.2021 00:50
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
    Solver()
    {
        heuristics["hamming"] = hamming;
        heuristics["manhattan"] = manhattan;
    }

    bool is_solvable(const State *final, const State *initial);
    void solve(const State *final, State *initial, const std::string &h);
    
private:
    std::map<std::string, void (*)(const State *, State *)> heuristics;
    PriorityQueue<State> opened, closed;

    void _left_move(const State *final,
            const State *intermediate, const std::string &h);
    void _right_move(const State *final,
            const State *intermediate, const std::string &h);
    void _up_move(const State *final,
            const State *intermediate, const std::string &h);
    void _down_move(const State *final,
            const State *intermediate, const std::string &h);
};

#endif
