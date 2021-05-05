/** * File              : solver.hpp
 * Author            : Rustam Khafizov <super.rustamm@gmail.com>
 * Date              : 25.03.2021 13:34
 * Last Modified Date: 05.05.2021 23:58
 * Last Modified By  : Rustam Khafizov <super.rustamm@gmail.com>
 */

#ifndef SOLVER_HPP
# define SOLVER_HPP

# include <unordered_map>
# include <algorithm>
# include <iostream>
# include <cstdint>
# include <string>
# include <cmath>
# include <queue>
# include <map>

# include "state.hpp"
# include "program-state.hpp"

class Comparator
{
public:
    bool operator()(State *left, State *right) const { return (*left > *right); }
};

State *hamming(const State *final, State *intermediate);
State *manhattan(const State *final, State *intermediate);
State *linear_conflicts(const State *final, State *intermediate);

class Solver
{
public:
    Solver()
    {
        heuristics["hamming"] = hamming;
        heuristics["manhattan"] = manhattan;
        heuristics["linear-conflicts"] = linear_conflicts;
    }

    bool  is_solvable(State *initial, const State *final);
    State *solve(State *initial, const State *final);
    
private:
    std::map<std::string, State *(*)(const State *, State *)> heuristics;
    std::priority_queue<State *, std::vector<State *>, Comparator> queue;
    std::unordered_map<std::string, State *> opened, closed;
    int64_t expanded_nodes{1}, visited_nodes{0};
};

#endif
