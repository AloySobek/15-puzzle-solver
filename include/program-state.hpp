/**
 * File              : program-state.hpp
 * Author            : Rustam Khafizov <super.rustamm@gmail.com>
 * Date              : 05.05.2021 19:19
 * Last Modified Date: 09.05.2021 19:34
 * Last Modified By  : Rustam Khafizov <super.rustamm@gmail.com>
 */

#ifndef PROGRAM_STATE_HPP
# define PROGRAM_STATE_HPP

# include <string>

# include "state.hpp"

class ProgramState
{
protected:
    ProgramState() { }

public:
    std::string puzzle_filename{""};
    std::string solution{"snail"};
    std::string heuristic{"manhattan"};
    std::string algorithm{"A*"};
    std::string algo_type{"UCS+GREEDY"};
    uint64_t    expanded_nodes{0};
    uint64_t    visited_nodes{0};
    int64_t    random_puzzle_size{3};

    ProgramState(ProgramState &) = delete;
    void operator=(const ProgramState &) = delete;

    static ProgramState *instance()
    {
        static ProgramState *instance_ = nullptr;

        if (!instance_)
            instance_ = new ProgramState();
        return (instance_);
    }

    static void destroy()
    {
        static ProgramState *instance_;

        if (instance_)
            delete instance_;
    }
};

#endif
