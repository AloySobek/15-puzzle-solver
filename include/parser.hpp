/**
 * File              : parser.hpp
 * Author            : Rustam Khafizov <super.rustamm@gmail.com>
 * Date              : 25.03.2021 15:05
 * Last Modified Date: 05.05.2021 22:56
 * Last Modified By  : Rustam Khafizov <super.rustamm@gmail.com>
 */

#ifndef PARSER_HPP
# define PARSER_HPP

# include <boost/program_options.hpp>
# include <exception>
# include <algorithm>
# include <iostream>
# include <cstdlib>
# include <fstream>
# include <cstdint>
# include <random>
# include <string>
# include <ctime>

# include "state.hpp"
# include "program-state.hpp"

namespace po = boost::program_options;

class Parser
{
public:
    Parser() { }

    void parse_cmd_options(int argc, char **argv);

    State *get_initial_state();
    const State *get_final_state();
    const std::string get_heuristic();

private:
    std::vector<std::string> possible_solution_patterns {
        "snail", "classic", "first-zero"
    };
    std::vector<std::string> possible_algorithm_types {
        "UCS+GREEDY", "UCS", "GREEDY"
    };
    std::vector<std::string> possible_heuristics {
        "hamming", "manhattan", "linear-conflicts", "database"
    };
    std::vector<std::string> possible_algorithms {
        "A*", "IDA*"
    };
    po::variables_map var_map;

    State *from_random(uint64_t n);
    State *from_lines(std::vector<std::string> &lines);
};

#endif
