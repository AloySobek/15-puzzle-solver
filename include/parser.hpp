/**
 * File              : parser.hpp
 * Author            : Rustam Khafizov <super.rustamm@gmail.com>
 * Date              : 25.03.2021 15:05
 * Last Modified Date: 10.04.2021 22:21
 * Last Modified By  : Rustam Khafizov <super.rustamm@gmail.com>
 */

#ifndef PARSER_HPP
# define PARSER_HPP

# include <boost/program_options.hpp>
# include <exception>
# include <iostream>
# include <fstream>
# include <cstdint>
# include <string>

# include "state.hpp"

namespace po = boost::program_options;

class Parser
{
public:
    Parser()
    {
        possible_heuristics.push_back("hamming");
        possible_heuristics.push_back("manhattan");
        possible_heuristics.push_back("linear-conflicts");
        possible_heuristics.push_back("database");

        possible_solution_patterns.push_back("snail");
        possible_solution_patterns.push_back("classic");
        possible_solution_patterns.push_back("first-zero");
    }

    void parse_cmd_options(int argc, char **argv);
    void parse_puzzle_file();

    State *get_initial_state();
    const State *get_final_state();

    const std::string get_heuristic();

private:
    std::vector<std::string> possible_solution_patterns;
    std::vector<std::string> possible_heuristics;
    std::vector<std::string> pzl_lines;
    po::variables_map        var_map;
};

#endif
