/** * File              : solver.hpp
 * Author            : Rustam Khafizov <super.rustamm@gmail.com>
 * Date              : 25.03.2021 13:34
 * Last Modified Date: 11.04.2021 23:52
 * Last Modified By  : Rustam Khafizov <super.rustamm@gmail.com>
 */

#ifndef SOLVER_HPP
# define SOLVER_HPP

# include <algorithm>
# include <iostream>
# include <cstdint>
# include <string>
# include <cmath>
# include <queue>
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
        heuristics["linear-conflicts"] = linear_conflicts;
    }

    bool is_solvable(const State *final, const State *initial);
    void solve(const State *final, State *initial, const std::string &h);
    
private:
    std::map<std::string, void (*)(const State *, State *)> heuristics;
    PriorityQueue<State> opened, closed;
    int64_t expanded_nodes{1}, visited_nodes{0};
};

#endif
