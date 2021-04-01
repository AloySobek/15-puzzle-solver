/**
 * File              : solver.hpp
 * Author            : Rustam Khafizov <super.rustamm@gmail.com>
 * Date              : 25.03.2021 13:34
 * Last Modified Date: 02.04.2021 01:24
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

# include "graph.hpp"
# include "queue.hpp"

int64_t _hamming(State *final_state, State *state)
{
    int64_t result{-1};

    for (uint64_t y{0}; y < final_state->puzzle.size(); ++y)
        for (uint64_t x{0}; x < final_state->puzzle[y].size(); ++x)
            if (state->puzzle[y][x] != final_state->puzzle[y][x])
                ++result;
    if (state->puzzle[state->puzzle.size() - 1][state->puzzle.size() -1] != 0)
        --result;
    return (result);
}

class Solver
{
public:
    Solver() { heuristics["hamming"] = _hamming; }

    void solve(State *final_state, State *initial_state, const std::string &heuristic)
    {
        bool solved{false};

        initial_state->f = heuristics[heuristic](final_state, initial_state);

        opened.push(initial_state);

        while (!opened.empty() && !solved)
        {
            State *state = opened.pop();

            if (state->puzzle == final_state->puzzle)
            {
                solved = true;
                state->print();
            }

            State *up = _up_move(final_state, state, heuristic);
            if (!opened.contains(up) && !closed.contains(up))
                opened.push(up);

            State *down = _down_move(final_state, state, heuristic);
            if (!opened.contains(down) && !closed.contains(down))
                opened.push(down);

            State *right = _right_move(final_state, state, heuristic);
            if (!opened.contains(right) && !closed.contains(right))
                opened.push(right);
            
            State *left = _left_move(final_state, state, heuristic);
            if (!opened.contains(left) && !closed.contains(left))
                opened.push(left);

            closed.push(state);
        }
    }

    void check_if_solvable(State *initial_state)
    {
        if (initial_state)
            return ;
        return ;        
    }

private:
    std::map<std::string, int64_t (*)(State *, State *)> heuristics;

    PriorityQueue<State> opened;
    PriorityQueue<State> closed;

    State *_up_move(State *final_state, State *state, const std::string &heuristic)
    {
        if (state->y - 1 < 0)
            return (nullptr);

        std::vector<std::vector<int64_t>> up_puzzle{state->puzzle};
        State *up_state{new State()};

        up_state->parent = state;
        up_state->puzzle = up_puzzle;
        up_state->g = state->g + 1;
        up_state->h = heuristics[heuristic](final_state, up_state);
        up_state->f = up_state->g + up_state->h;
        up_state->y = state->y - 1;
        up_state->x = state->x;

        int64_t tmp = up_state->puzzle[up_state->y][up_state->x];

        up_state->puzzle[state->y - 1][state->x] = state->puzzle[state->y][state->x];
        up_state->puzzle[state->y][state->x] = tmp;
        return (up_state);
    }

    State *_down_move(State *final_state, State *state, const std::string &heuristic)
    {
        if ((uint64_t)(state->y + 1) >= state->puzzle.size())
            return (nullptr);

        std::vector<std::vector<int64_t>> down_puzzle{state->puzzle};
        State *down_state{new State()};

        down_state->parent = state;
        down_state->puzzle = down_puzzle;
        down_state->g = state->g + 1;
        down_state->h = heuristics[heuristic](final_state, down_state);
        down_state->f = down_state->g + down_state->h;
        down_state->y = state->y + 1;
        down_state->x = state->x;

        int64_t tmp = down_state->puzzle[down_state->y][down_state->x];

        down_state->puzzle[state->y + 1][state->x] = state->puzzle[state->y][state->x];
        down_state->puzzle[state->y][state->x] = tmp;
        return (down_state);
    }

    State *_right_move(State *final_state, State *state, const std::string &heuristic)
    {
        if ((uint64_t)(state->x + 1) >= state->puzzle.size())
            return (nullptr);

        std::vector<std::vector<int64_t>> down_puzzle{state->puzzle};
        State *down_state{new State()};

        down_state->parent = state;
        down_state->puzzle = down_puzzle;
        down_state->g = state->g + 1;
        down_state->h = heuristics[heuristic](final_state, down_state);
        down_state->f = down_state->g + down_state->h;
        down_state->y = state->y;
        down_state->x = state->x + 1;

        int64_t tmp = down_state->puzzle[down_state->y][down_state->x];

        down_state->puzzle[state->y][state->x + 1] = state->puzzle[state->y][state->x];
        down_state->puzzle[state->y][state->x] = tmp;
        return (down_state);
    }

    State *_left_move(State *final_state, State *state, const std::string &heuristic)
    {
        if (state->x - 1 < 0)
            return (nullptr);

        std::vector<std::vector<int64_t>> down_puzzle{state->puzzle};
        State *down_state{new State()};

        down_state->parent = state;
        down_state->puzzle = down_puzzle;
        down_state->g = state->g + 1;
        down_state->h = heuristics[heuristic](final_state, down_state);
        down_state->f = down_state->g + down_state->h;
        down_state->y = state->y;
        down_state->x = state->x - 1;

        int64_t tmp = down_state->puzzle[down_state->y][down_state->x];

        down_state->puzzle[state->y][state->x - 1] = state->puzzle[state->y][state->x];
        down_state->puzzle[state->y][state->x] = tmp;
        return (down_state);
    }
};

#endif
