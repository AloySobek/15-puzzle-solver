/**
 * File              : state.hpp
 * Author            : Rustam Khafizov <super.rustamm@gmail.com>
 * Date              : 29.03.2021 00:27
 * Last Modified Date: 11.04.2021 23:48
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
    std::vector<int64_t> pzl;
    const State *parent{nullptr};
    int64_t g{0}, h{0}, i{0}, n{0};

    State() { }

    State(const State *other)
    {
        this->pzl = other->pzl;
        this->parent = other;
        this->g = other->g;
        this->h = other->h;
        this->i = other->i;
        this->n = other->n;
    }
    
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

    friend std::ostream &operator<<(std::ostream &os, const State &obj)
    {
        std::cout << obj.g + obj.h;
        return (os);
    }

    void print() const
    {
        for (uint64_t i{0}, size{pzl.size()}; i < size; ++i)
            std::cout << pzl[i] << " ";
        std::cout << std::endl;
    }
};

#endif
