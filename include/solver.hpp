/**
 * File              : solver.hpp
 * Author            : Rustam Khafizov <super.rustamm@gmail.com>
 * Date              : 25.03.2021 13:34
 * Last Modified Date: 31.03.2021 01:03
 * Last Modified By  : Rustam Khafizov <super.rustamm@gmail.com>
 */

#ifndef SOLVER_HPP
# define SOLVER_HPP

# include <cmath>
# include <queue>
# include <cstdint>
# include <iostream>
# include <algorithm>

# include "graph.hpp"

class Solver
{
public:
    Solver() {}

    void solve(Node<State, int32_t> *initial_node)
    {
        bool solved = false;

        in_progress_states.push(initial_node);

        while (!in_progress_states.empty() && !solved)
        {
            Node<State, int32_t> *node = in_progress_states.top();
        }
    }

    void check_if_solvable(NodeBase *initial_node)
    {
        return;        
    }
private:
    std::priority_queue<Node<State, int32_t> *> in_progress_states;
    std::vector<Node<State, int32_t> *> promising_states;
    std::vector<Node<State, int32_t> *> visited_states;
};
#endif
