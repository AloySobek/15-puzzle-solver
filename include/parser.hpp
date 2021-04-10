/**
 * File              : parser.hpp
 * Author            : Rustam Khafizov <super.rustamm@gmail.com>
 * Date              : 25.03.2021 15:05
 * Last Modified Date: 09.04.2021 23:19
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
    Parser() : pzl_n{0} {}

    void parse_cmd_options(int argc, char **argv);
    void parse_puzzle_file();

    State *get_initial_state();
    const State *get_final_state();

    const std::string get_heuristic();

private:
    std::vector<std::string> pzl_lines;
    po::variables_map        var_map;
    int64_t                  pzl_n;
};

#endif
