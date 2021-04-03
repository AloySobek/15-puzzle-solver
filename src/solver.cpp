/**
 * File              : solver.cpp
 * Author            : Rustam Khafizov <super.rustamm@gmail.com>
 * Date              : 02.04.2021 21:57
 * Last Modified Date: 03.04.2021 18:30
 * Last Modified By  : Rustam Khafizov <super.rustamm@gmail.com>
 */

#include "solver.hpp"

void Solver::solve(State *final, State *initial, const std::string &heuristic)
{
    State *intermediate{nullptr};

    initial->f = heuristics[heuristic](final, initial);
    opened.push(initial);

    for (intermediate = opened.pop(); intermediate->pzl != final->pzl; intermediate = opened.pop())
    {
        State *up = _up_move(final, intermediate, heuristic);
        if (!opened.contains(up) && !closed.contains(up))
            opened.push(up);
        State *down = _down_move(final, intermediate, heuristic);
        if (!opened.contains(down) && !closed.contains(down))
            opened.push(down);
        State *right = _right_move(final, intermediate, heuristic);
        if (!opened.contains(right) && !closed.contains(right))
            opened.push(right);
        State *left = _left_move(final, intermediate, heuristic);
        if (!opened.contains(left) && !closed.contains(left))
            opened.push(left);
        closed.push(intermediate);
    }
    intermediate->print();
}

bool Solver::is_solvable(State *initial_state)
{
    int64_t inv_count = _get_inversion_count(initial_state->pzl);

    if (initial_state->pzl.size() & 1)
        return (!(inv_count & 1));
    else
    {
        int64_t pos = _find_zero(initial_state->pzl);
        if (pos & 1)
            return (!(inv_count & 1));
        return (inv_count & 1);
    }
}

State *Solver::_up_move(State *final_state, State *state, const std::string &heuristic)
{
    if (state->y - 1 < 0)
        return (nullptr);

    State *up_state{new State()};

    up_state->pzl = state->pzl;
    up_state->parent = state;

    up_state->pzl[state->y][state->x] = state->pzl[state->y - 1][state->x];
    up_state->pzl[state->y - 1][state->x] = 0;

    up_state->y = state->y - 1;
    up_state->x = state->x;

    up_state->g = state->g + 1;
    up_state->h = heuristics[heuristic](final_state, up_state);
    up_state->f = up_state->g + up_state->h;

    return (up_state);
}

State *Solver::_down_move(State *final_state, State *state, const std::string &heuristic)
{
    if ((uint64_t)(state->y + 1) >= state->pzl.size())
        return (nullptr);

    State *down_state{new State()};

    down_state->pzl = state->pzl;
    down_state->parent = state;

    down_state->pzl[state->y][state->x] = state->pzl[state->y + 1][state->x];
    down_state->pzl[state->y + 1][state->x] = 0;

    down_state->g = state->g + 1;
    down_state->h = heuristics[heuristic](final_state, down_state);
    down_state->f = down_state->g + down_state->h;

    down_state->y = state->y + 1;
    down_state->x = state->x;

    return (down_state);
}

State *Solver::_right_move(State *final_state, State *state, const std::string &heuristic)
{
    if ((uint64_t)(state->x + 1) >= state->pzl.size())
        return (nullptr);

    State *right_state{new State()};

    right_state->pzl = state->pzl;
    right_state->parent = state;

    right_state->pzl[state->y][state->x] = state->pzl[state->y][state->x + 1];
    right_state->pzl[state->y][state->x + 1] = 0;

    right_state->g = state->g + 1;
    right_state->h = heuristics[heuristic](final_state, right_state);
    right_state->f = right_state->g + right_state->h;

    right_state->y = state->y;
    right_state->x = state->x + 1;

    return (right_state);
}

State *Solver::_left_move(State *final_state, State *state, const std::string &heuristic)
{
    if (state->x - 1 < 0)
        return (nullptr);

    State *left_state{new State()};

    left_state->pzl = state->pzl;
    left_state->parent = state;

    left_state->pzl[state->y][state->x] = state->pzl[state->y][state->x - 1];
    left_state->pzl[state->y][state->x - 1] = 0;

    left_state->g = state->g + 1;
    left_state->h = heuristics[heuristic](final_state, left_state);
    left_state->f = left_state->g + left_state->h;

    left_state->y = state->y;
    left_state->x = state->x - 1;

    return (left_state);
}
    
int64_t Solver::_get_inversion_count(std::vector<std::vector<int64_t>> &puzzle)
{
    int64_t *array{new int64_t[puzzle.size() * puzzle.size()]};
    int64_t count = 0;

    for (uint64_t i{0}; i < puzzle.size(); ++i)
        for (uint64_t j{0}; j < puzzle.size(); ++j)
            array[puzzle.size() * i + j] = puzzle[i][j];

    for (uint64_t i{0}; i < puzzle.size() * puzzle.size() - 1; ++i)
        for (uint64_t j{i + 1}; j < puzzle.size() * puzzle.size(); ++j)
            if (array[j] && array[i] && array[i] > array[j])
                count++;
    return (count);
}

int64_t Solver::_find_zero(std::vector<std::vector<int64_t>> &puzzle)
{
    for (int64_t i{(int64_t)puzzle.size() - 1}; i >= 0; --i)
        for (int64_t j{(int64_t)puzzle.size() - 1}; j >= 0; --j)
            if (puzzle[i][j] == 0)
                return puzzle.size() - i;
    return (0);
}

/* template<class Lambda> */
/* State *_expand(State *current_state, Lambda possible, Lambda move, Lambda heuristic) */
/* { */
/*     if (!possible()) */
/*         return (nullptr); */

/*     State *state{new State()}; */

/*     state->pzl = current_state->pzl; */
/*     state->parent = current_state; */

/*     move(state); */

/*     state->g = state->g + 1; */
/*     state->h = heuristic(); */
/*     state->f = state->g + state->h; */

/*     return (state); */
/* } */
