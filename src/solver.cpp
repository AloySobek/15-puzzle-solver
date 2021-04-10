/**
 * File              : solver.cpp
 * Author            : Rustam Khafizov <super.rustamm@gmail.com>
 * Date              : 02.04.2021 21:57
 * Last Modified Date: 10.04.2021 16:37
 * Last Modified By  : Rustam Khafizov <super.rustamm@gmail.com>
 */

#include "solver.hpp"
#include <queue>

bool Solver::is_solvable(const State *final, const State *initial)
{
    int64_t n = initial->pzl.size();
    int64_t *final_array{new int64_t[n * n]};
    int64_t *initial_array{new int64_t[n * n]};
    int64_t inv_count{0};
    bool    parity;

    parity = ((std::max(final->x, initial->x) - std::min(final->x, initial->x))
           + (std::max(final->y, initial->y) - std::min(final->y, initial->y)))
           % 2;

    for (int64_t i{0}; i < n; ++i)
        for (int64_t j{0}; j < n; ++j)
            final_array[n * i + j] = final->pzl[i][j];

    for (int64_t i{0}; i < n; ++i)
        for (int64_t j{0}; j < n; ++j)
            initial_array[n * i + j] = initial->pzl[i][j];

    for (int64_t i{0}; i < n * n; ++i)
        for (int64_t j{i}; j < n * n; ++j)
            if (final_array[i] == initial_array[j])
            {
                for (; j != i; ++inv_count, --j)
                {
                    int64_t tmp = initial_array[j - 1];
                    initial_array[j - 1] = initial_array[j];
                    initial_array[j] = tmp;
                }
                break;
            }

    delete[] final_array;
    delete[] initial_array;

    if (parity) // is odd
        return (inv_count % 2);
    return (!(inv_count % 2)); // is even
}

void Solver::solve(const State *final, State *initial, const std::string &h)
{
    heuristics[h](final, initial);
    opened.push(initial);

    while (!opened.empty())
    {
        State *intermediate = opened.top();

        if (intermediate->pzl == final->pzl)
        {
            intermediate->print();
            break;
        }

        _left_move(final, intermediate, h);
        _right_move(final, intermediate, h);
        _up_move(final, intermediate, h);
        _down_move(final, intermediate, h);

        opened.pop();
        closed.push(intermediate);
    }
}

void Solver::_left_move(const State *final,
        const State *intermediate, const std::string &h)
{
    if (intermediate->x - 1 < 0) return ;

    State *left{new State()};
    left->copy(intermediate);

    left->pzl[left->y][left->x] = left->pzl[left->y][left->x - 1];
    left->pzl[left->y][left->x - 1] = 0;
    heuristics[h](final, left);
    left->g += 1;
    left->x -= 1;

    if (!closed.contains(left))
    {
        State *tmp = opened.contains(left);
        if (!tmp || tmp->g > intermediate->g)
            opened.push(left);
    }
}

void Solver::_right_move(const State *final,
        const State *intermediate, const std::string &h)
{
    if (intermediate->x + 1 >= (int64_t)final->pzl.size()) return ;

    State *right = new State();
    right->copy(intermediate);

    right->pzl[right->y][right->x] = right->pzl[right->y][right->x + 1];
    right->pzl[right->y][right->x + 1] = 0;
    heuristics[h](final, right);
    right->g += 1;
    right->x += 1;

    if (!closed.contains(right))
    {
        State *tmp = opened.contains(right);
        if (!tmp || tmp->g > intermediate->g)
            opened.push(right);
    }
}

void Solver::_up_move(const State *final,
        const State *intermediate, const std::string &h)
{
    if (intermediate->y - 1 < 0) return ;
    State *up{new State()};
    up->copy(intermediate);

    up->pzl[up->y][up->x] = up->pzl[up->y - 1][up->x];
    up->pzl[up->y - 1][up->x] = 0;
    heuristics[h](final, up);
    up->g += 1;
    up->y -= 1;

    if (!closed.contains(up))
    {
        State *tmp = opened.contains(up);
        if (!tmp || tmp->g > intermediate->g)
            opened.push(up);
    }
}

void Solver::_down_move(const State *final,
        const State *intermediate, const std::string &h)
{
    if (intermediate->y + 1 >= (int64_t)final->pzl.size()) return ;

    State *down{new State()};
    down->copy(intermediate);

    down->pzl[down->y][down->x] = down->pzl[down->y + 1][down->x];
    down->pzl[down->y + 1][down->x] = 0;
    heuristics[h](final, down);
    down->g += 1;
    down->y += 1;

    if (!closed.contains(down))
    {
        State *tmp = opened.contains(down);
        if (!tmp || tmp->g > intermediate->g)
            opened.push(down);
    }
}
