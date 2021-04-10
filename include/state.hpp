/**
 * File              : state.hpp
 * Author            : Rustam Khafizov <super.rustamm@gmail.com>
 * Date              : 29.03.2021 00:27
 * Last Modified Date: 10.04.2021 12:53
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
    const State *parent{nullptr};
    int64_t g{0}, h{0};
    int64_t x{0}, y{0};
    
    friend bool operator<(const State &l, const State &r)
    {
        return (l.g + l.h < r.g + r.h);
    }
    friend bool operator>(const State &l, const State &r)
    {
        return (l.g + l.h > r.g + r.h);
    }

    friend bool operator>=(const State &l, const State &r)
    {
        return (l.g + l.h >= r.g + r.h);
    }
    friend bool operator<=(const State &l, const State &r)
    {
        return (l.g + l.h <= r.g + r.h);
    }

    friend bool operator==(const State &l, const State &r)
    {
        for (uint64_t i{0}; i < l.pzl.size(); ++i)
            for (uint64_t j{0}; j < l.pzl.size(); ++j)
                if (l.pzl[i][j] != r.pzl[i][j])
                    return (false);
        return (true);
    }

    friend std::ostream &operator<<(std::ostream &os, const State &obj)
    {
        std::cout << obj.g + obj.h;
        return (os);
    }

    void copy(const State *other)
    {
        this->pzl = other->pzl;
        this->parent = other;
        this->g = other->g;
        this->h = other->h;
        this->x = other->x;
        this->y = other->y;
    }

    void print() const;

    ~State()
    {
        std::cout << "Deleted" << std::endl;
    }
};

#endif
