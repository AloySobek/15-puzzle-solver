/**
 * File              : solver.cpp
 * Author            : Rustam Khafizov <super.rustamm@gmail.com>
 * Date              : 02.04.2021 21:57
 * Last Modified Date: 11.04.2021 23:47
 * Last Modified By  : Rustam Khafizov <super.rustamm@gmail.com>
 */

#include "solver.hpp"
#include <queue>

bool Solver::is_solvable(const State *final, const State *initial)
{
    uint64_t inv_count{0};
    State   *tmp{new State(initial)};
    bool    parity;

    parity = ((std::max(final->i % final->n, tmp->i % final->n)
               - std::min(final->i % final->n, tmp->i % final->n))
           + (std::max(final->i / final->n, tmp->i / final->n)
               - std::min(final->i / final->n, tmp->i / final->n)))
           % 2;

    for (uint64_t i{0}, isize{final->pzl.size()}; i < isize; ++i)
        for (uint64_t j{i}, jsize{final->pzl.size()}; j < jsize; ++j)
            if (final->pzl[i] == tmp->pzl[j])
            {
                for (; j != i; ++inv_count, --j)
                {
                    int64_t t = tmp->pzl[j - 1];
                    tmp->pzl[j - 1] = tmp->pzl[j];
                    tmp->pzl[j] = t;
                }
                break;
            }

    delete tmp;

    if (parity) // is odd
        return (inv_count % 2);
    return (!(inv_count % 2)); // is even
}

void Solver::solve(const State *final, State *initial, const std::string &h)
{
    State *tmp;

    heuristics[h](final, initial);
    opened.push(initial);

    while (!opened.empty())
    {
        State *intermediate = opened.top();
        closed.push(intermediate), ++visited_nodes;
        opened.pop();

        if (intermediate->h == 0)
        {
            std::cout << "Success!" << std::endl;
            std::cout << "Memory: " << expanded_nodes << std::endl;
            std::cout << "Time: " << visited_nodes << std::endl;

            while (intermediate->parent)
            {
                intermediate->print();
                intermediate = (State *)intermediate->parent;
            }
            break;
        }

        if ((intermediate->i % intermediate->n) - 1 >= 0)
        {
            State *left{new State(intermediate)};
            left->pzl[left->i] = left->pzl[left->i - 1]; 
            left->pzl[left->i - 1] = 0;
            heuristics[h](final, left);
            left->g += 1;
            left->i -= 1;
            if (!closed.contains(left))
                if (!(tmp = opened.contains(left)) || tmp->g > intermediate->g)
                    opened.push(left), ++expanded_nodes;
        }
        if ((intermediate->i % intermediate->n) + 1 < intermediate->n)
        {
            State *right{new State(intermediate)};
            right->pzl[right->i] = right->pzl[right->i + 1];
            right->pzl[right->i + 1] = 0;
            heuristics[h](final, right);
            right->g += 1;
            right->i += 1;
            if (!closed.contains(right))
                if (!(tmp = opened.contains(right)) || tmp->g > intermediate->g)
                    opened.push(right), ++expanded_nodes;
        }
        if ((intermediate->i / intermediate->n) - 1 >= 0)
        {
            State *up{new State(intermediate)};
            up->pzl[up->i] = up->pzl[up->i - up->n];
            up->pzl[up->i - up->n] = 0;
            heuristics[h](final, up);
            up->g += 1;
            up->i -= up->n;
            if (!closed.contains(up))
                if (!(tmp = opened.contains(up)) || tmp->g > intermediate->g)
                    opened.push(up), ++expanded_nodes;
        }
        if ((intermediate->i / intermediate->n) + 1 < intermediate->n)
        {
            State *down{new State(intermediate)};
            down->pzl[down->i] = down->pzl[down->i + down->n];
            down->pzl[down->i + down->n] = 0;
            heuristics[h](final, down);
            down->g += 1;
            down->i += down->n;
            if (!closed.contains(down))
                if (!(tmp = opened.contains(down)) || tmp->g > intermediate->g)
                    opened.push(down), ++expanded_nodes;
        }
        std::cout << visited_nodes << std::endl;
    }
}
