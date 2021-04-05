/**
 * File              : state.hpp
 * Author            : Rustam Khafizov <super.rustamm@gmail.com>
 * Date              : 29.03.2021 00:27
 * Last Modified Date: 05.04.2021 17:17
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
    std::vector<std::vector<int64_t>> pzl;
    State *parent{nullptr};
    int64_t g{0}, h{0}, f{0};
    int64_t x{0}, y{0};
    
    State() {}

    friend bool operator<(const State &l, const State &r) { return (l.f < r.f); }
    friend bool operator>(const State &l, const State &r) { return (l.f > r.f); }

    friend bool operator>=(const State &l, const State &r) { return (l.f >= r.f); }
    friend bool operator<=(const State &l, const State &r) { return (l.f <= r.f); }

    friend bool operator==(const State &l, const State &r)
    {
        return (l.pzl == r.pzl);
    }

    friend std::ostream &operator<<(std::ostream &os, const State &obj)
    {
        std::cout << obj.f;
        return (os);
    }

    void print() const;
};

#endif
