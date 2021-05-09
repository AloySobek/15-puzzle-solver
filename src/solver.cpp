/**
 * File              : solver.cpp
 * Author            : Rustam Khafizov <super.rustamm@gmail.com>
 * Date              : 02.04.2021 21:57
 * Last Modified Date: 09.05.2021 18:14
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

    if (parity)
        return (inv_count % 2); // is odd
    return (!(inv_count % 2));  // is even
}

State *Solver::solve(State *initial, const State *final)
{
    queue.push(heuristics[ProgramState::instance()->heuristic](final, initial));
    opened[initial->to_string()] = initial;

    while (!queue.empty())
    {
        State *intermediate = queue.top();
        queue.pop();

        ++ProgramState::instance()->visited_nodes;

        if (intermediate->pzl == final->pzl)
            return (intermediate);
        
        opened.erase(intermediate->to_string());
        if (closed.find(intermediate->to_string()) != closed.end())
            delete closed[intermediate->to_string()];
        closed[intermediate->to_string()] = intermediate;

        if ((int64_t)(intermediate->zero_position % intermediate->size) - 1 >= 0)
        {
            State *left{new State(intermediate)};
            left->pzl[left->zero_position] = left->pzl[left->zero_position - 1]; 
            left->pzl[left->zero_position - 1] = 0;
            left->zero_position -= 1;
            if (!analyze_state(left, final)) delete left;
        }
        if ((intermediate->zero_position % intermediate->size) + 1 < intermediate->size)
        {
            State *right{new State(intermediate)};
            right->pzl[right->zero_position] = right->pzl[right->zero_position + 1];
            right->pzl[right->zero_position + 1] = 0;
            right->zero_position += 1;
            if (!analyze_state(right, final)) delete right;
        }
        if ((int64_t)(intermediate->zero_position / intermediate->size) - 1 >= 0)
        {
            State *up{new State(intermediate)};
            up->pzl[up->zero_position] = up->pzl[up->zero_position - up->size];
            up->pzl[up->zero_position - up->size] = 0;
            up->zero_position -= up->size;
            if (!analyze_state(up, final)) delete up;
        }
        if ((intermediate->zero_position / intermediate->size) + 1 < intermediate->size)
        {
            State *down{new State(intermediate)};
            down->pzl[down->zero_position] = down->pzl[down->zero_position + down->size];
            down->pzl[down->zero_position + down->size] = 0;
            down->zero_position += down->size;
            if (!analyze_state(down, final)) delete down;
        }
    }
    return (nullptr);
}

State *Solver::solve_ida(State *initial, const State *final)
{
    heuristics[ProgramState::instance()->heuristic](final, initial);
    if (initial->pzl == final->pzl)
        return (nullptr);
    return (nullptr);
}

/* State *Solver::solve_ida_search(State *intermediate, uint64_t g, uint64_t threshold) */
/* { */
        
/* } */

bool Solver::analyze_state(State *candidate, const State *final)
{
    candidate->g += ProgramState::instance()->algo_type == "GREEDY" ? 0 : 1;
    heuristics[ProgramState::instance()->heuristic](final, candidate);
    candidate->h = ProgramState::instance()->algo_type == "UCS" ? 0 : candidate->h;
    if (closed.find(candidate->to_string()) == closed.end())
    {
        if (opened.find(candidate->to_string()) == opened.end())
        {
            opened[candidate->to_string()] = candidate;
            queue.push(candidate), ++ProgramState::instance()->expanded_nodes;
            return (true);
        }
        else
        {
            if (opened[candidate->to_string()]->g > candidate->g)
            {
                opened[candidate->to_string()] = candidate;
                queue.push(candidate), ++ProgramState::instance()->expanded_nodes;
                return (true);
            }
        }
    }
    return (false);
}

Solver::~Solver()
{
    for (auto i = closed.begin(); i != closed.end(); i = closed.erase(i))
        delete i->second;
    while (!queue.empty())
    {
        State *tmp = queue.top();
        queue.pop();
        if (opened.find(tmp->to_string()) != opened.end())
            opened.erase(tmp->to_string());
        delete tmp;
    }
    for (auto i = opened.begin(); i != opened.end(); i = opened.erase(i))
        delete i->second;
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
    uint64_t conflicts{0};
    uint64_t pR[(final->size * final->size) + 1];
    uint64_t pC[(final->size * final->size) + 1];

    // Save intermediate row/column to accelerate check whether or not
    // tile pair in the same row/column and check if tile pair in conflict
    //
    //  t1(x) -  -  and  t1 - - -> - - t2
    //    -   -  -     t2 to the left of t1
    //  t2(1) -  -
    //
    for (uint64_t r = 0; r < final->size; r++) {
        for (uint64_t c = 0; c < final->size; c++) {
            pR[intermediate->pzl[(r * final->size) + c]] = r;
            pC[intermediate->pzl[(r * final->size) + c]] = c;
        }
    }
    for (uint64_t r{0}; r < final->size; r++) {
        for (uint64_t cl{0}; cl < final->size; cl++) {
            for (uint64_t cr = cl + 1; cr < final->size; cr++) {
                if (final->pzl[(r * final->size) + cl]
                    && final->pzl[(r * final->size) + cr]
                    && r == pR[final->pzl[(r * final->size) + cl]]
                    && pR[final->pzl[(r * final->size) + cl]] == pR[final->pzl[(r * final->size) + cr]]
                    && pC[final->pzl[(r * final->size) + cl]] > pC[final->pzl[(r * final->size) + cr]])
                        ++conflicts;
            }
        }
    }
    for (uint64_t c = 0; c < final->size; c++) {
        for (uint64_t rU = 0; rU < final->size; rU++) {
            for (uint64_t rD = rU + 1; rD < final->size; rD++) {
                if (final->pzl[(rU * final->size) + c]
                    && final->pzl[(rD * final->size)]
                    && c == pC[final->pzl[(rU * final->size)]]
                    && pC[final->pzl[(rU * final->size)]] == pC[final->pzl[(rD * final->size)]]
                    && pR[final->pzl[(rU * final->size)]] > pR[final->pzl[(rD * final->size)]]) {
                        ++conflicts;
                }
            }
        }
    }
    manhattan(final, intermediate); intermediate->h += 2 * conflicts;
    return (intermediate);
}
