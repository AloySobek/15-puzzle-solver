/**
 * File              : solver.cpp
 * Author            : Rustam Khafizov <super.rustamm@gmail.com>
 * Date              : 02.04.2021 21:57
 * Last Modified Date: 06.05.2021 00:01
 * Last Modified By  : Rustam Khafizov <super.rustamm@gmail.com>
 */

#include "solver.hpp"

bool Solver::is_solvable(State *initial, const State *final)
{
    uint64_t size{final->size};
    uint64_t inv_count{0};
    State    *tmp{new State(initial)};
    bool     parity;

    parity = ((std::max(final->zero_position % size, initial->zero_position % size)
                - std::min(final->zero_position % size, initial->zero_position % size))
           + (std::max(final->zero_position / size, initial->zero_position / size)
                - std::min(final->zero_position / size, initial->zero_position / size)))
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

State *Solver::solve(State *initial, const State *final)
{
    queue.push(heuristics[ProgramState::instance()->heuristic](final, initial));
    opened[initial->to_string()] = initial;

    while (!queue.empty() && ++visited_nodes)
    {
        State *intermediate = queue.top();
        queue.pop();

        if (intermediate->h == 0)
            return (intermediate);

        opened.erase(intermediate->to_string());
        closed[intermediate->to_string()] = intermediate;

        if ((int64_t)(intermediate->zero_position % intermediate->size) - 1 >= 0)
        {
            State *left{new State(intermediate)};
            left->pzl[left->zero_position] = left->pzl[left->zero_position - 1]; 
            left->pzl[left->zero_position - 1] = 0;
            heuristics[ProgramState::instance()->heuristic](final, left);
            left->g += 1;
            left->zero_position -= 1;

            if (closed.find(left->to_string()) == closed.end())
            {
                if (opened.find(left->to_string()) == opened.end())
                {
                    opened[left->to_string()] = left;
                    queue.push(left), ++expanded_nodes;
                }
                else
                {
                    if (opened[left->to_string()]->g > left->g)
                    {
                        opened[left->to_string()] = left;
                        queue.push(left), ++expanded_nodes;
                    }
                }
            }
        }
        if ((intermediate->zero_position % intermediate->size) + 1 < intermediate->size)
        {
            State *right{new State(intermediate)};
            right->pzl[right->zero_position] = right->pzl[right->zero_position + 1];
            right->pzl[right->zero_position + 1] = 0;
            heuristics[ProgramState::instance()->heuristic](final, right);
            right->g += 1;
            right->zero_position += 1;

            if (closed.find(right->to_string()) == closed.end())
            {
                if (opened.find(right->to_string()) == opened.end())
                {
                    opened[right->to_string()] = right;
                    queue.push(right), ++expanded_nodes;
                }
                else
                {
                    if (opened[right->to_string()]->g > right->g)
                    {
                        opened[right->to_string()] = right;
                        queue.push(right), ++expanded_nodes;
                    }
                }
            }
        }
        if ((int64_t)(intermediate->zero_position / intermediate->size) - 1 >= 0)
        {
            State *up{new State(intermediate)};
            if (up->zero_position < 0 || up->zero_position - 1 < 0)
                std::cout << "Alert!" << std::endl;
            up->pzl[up->zero_position] = up->pzl[up->zero_position - up->size];
            up->pzl[up->zero_position - up->size] = 0;
            heuristics[ProgramState::instance()->heuristic](final, up);
            up->g += 1;
            up->zero_position -= up->size;

            if (closed.find(up->to_string()) == closed.end())
            {
                if (opened.find(up->to_string()) == opened.end())
                {
                    opened[up->to_string()] = up;
                    queue.push(up), ++expanded_nodes;
                }
                else
                {
                    if (opened[up->to_string()]->g > up->g)
                    {
                        opened[up->to_string()] = up;
                        queue.push(up), ++expanded_nodes;
                    }
                }
            }
        }
        if ((intermediate->zero_position / intermediate->size) + 1 < intermediate->size)
        {
            State *down{new State(intermediate)};
            down->pzl[down->zero_position] = down->pzl[down->zero_position + down->size];
            down->pzl[down->zero_position + down->size] = 0;
            heuristics[ProgramState::instance()->heuristic](final, down);
            down->g += 1;
            down->zero_position += down->size;

            if (closed.find(down->to_string()) == closed.end())
            {
                if (opened.find(down->to_string()) == opened.end())
                {
                    opened[down->to_string()] = down;
                    queue.push(down), ++expanded_nodes;
                }
                else
                {
                    if (opened[down->to_string()]->g > down->g)
                    {
                        opened[down->to_string()] = down;
                        queue.push(down), ++expanded_nodes;
                    }
                }
            }
        }
    }
    return (nullptr);
}

State *hamming(const State *final, State *intermediate)
{
    intermediate->h = 0;

    for (uint64_t i{0}, size{final->pzl.size()}; i < size; ++i)
        if (intermediate->pzl[i] != 0 && intermediate->pzl[i] != final->pzl[i])
            ++(intermediate->h);
    return (intermediate);
}

State *manhattan(const State *final, State *intermediate)
{
    uint64_t size{final->size};
    intermediate->h = 0;

    for (uint64_t i{0}, isize{final->pzl.size()}; i < isize; ++i)
        if (intermediate->pzl[i] != 0 && intermediate->pzl[i] != final->pzl[i])
            for (uint64_t j{0}, jsize{final->pzl.size()}; j < jsize; ++j)
                if (intermediate->pzl[j] == final->pzl[i])
                    intermediate->h += (std::max(i % size, j % size) -
                                        std::min(i % size, j % size)) +
                                       (std::max(i / size, j / size) -
                                        std::min(i / size, j / size));
    return (intermediate);
}

State *linear_conflicts(const State *final, State *intermediate)
{
    manhattan(final, intermediate);
    return (intermediate);
}
