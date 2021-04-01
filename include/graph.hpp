/**
 * File              : graph.hpp
 * Author            : Rustam Khafizov <super.rustamm@gmail.com>
 * Date              : 29.03.2021 00:27
 * Last Modified Date: 02.04.2021 01:46
 * Last Modified By  : Rustam Khafizov <super.rustamm@gmail.com>
 */

#ifndef GRAPH_HPP
# define GRAPH_HPP

# include <vector>
# include <cstdint>
# include <iostream>

class State
{
public:
    std::vector<std::vector<int64_t>> puzzle;
    State *parent;
    int64_t g{0};
    int64_t h;
    int64_t f;

    int64_t x;
    int64_t y;
    
    State() {}

    void print() const
    {
        for (uint64_t y{0}; y < puzzle.size(); ++y, std::cout << std::endl)
            for (uint64_t x{0}; x < puzzle[y].size(); ++x)
                std::cout << puzzle[y][x] << " ";
    }

    friend bool operator<(const State &l, const State &r) { return (l.f < r.f); }
    friend bool operator>(const State &l, const State &r) { return (l.f > r.f); }
    friend bool operator>=(const State &l, const State &r) { return (l.f >= r.f); }
    friend bool operator<=(const State &l, const State &r) { return (l.f <= r.f); }

    friend bool operator==(const State &l, const State &r)
    {
        l.print();
        r.print();

        for (uint64_t y{0}; y < l.puzzle.size(); ++y)
            for (uint64_t x{0}; x < l.puzzle[y].size(); ++x)
                if (l.puzzle[y][x] != r.puzzle[y][x])
                    return (false);
        return (true);
    }

    friend std::ostream &operator<<(std::ostream &os, const State &obj)
    {
        std::cout << obj.g + obj.h;
        return (os);
    }
};

#endif
