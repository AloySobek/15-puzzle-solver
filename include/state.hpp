/**
 * File              : state.hpp
 * Author            : Rustam Khafizov <super.rustamm@gmail.com>
 * Date              : 29.03.2021 00:27
 * Last Modified Date: 08.05.2021 22:16
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
    std::vector<int64_t> pzl;     // Puzzle itself in 1d array
    const State *parent{nullptr}; // For path reconstruction
    uint64_t zero_position{0};    // Where is empty tile located
    uint64_t size{0};             // Size of one side of puzzle
    uint64_t g{0};                // Distance from source
    uint64_t h{0};                // Distance to destination

    State() { }
    State(const State *other);

    std::string to_string() const;
    std::string row_to_string(uint64_t n) const;

    friend bool operator<(const State &l, const State &r)
    {
        return ((l.g + l.h) < (r.g + r.h));
    }
    friend bool operator>(const State &l, const State &r)
    {
        return ((l.g + l.h) > (r.g + r.h));
    }
    friend bool operator>=(const State &l, const State &r)
    {
        return ((l.g + l.h) >= (r.g + r.h));
    }
    friend bool operator<=(const State &l, const State &r)
    {
        return ((l.g + l.h) <= (r.g + r.h));
    }
    friend bool operator==(const State &l, const State &r)
    {
        return (l.pzl == r.pzl);
    }
};

#endif
