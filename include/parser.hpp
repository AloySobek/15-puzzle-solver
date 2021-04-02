/**
 * File              : parser.hpp
 * Author            : Rustam Khafizov <super.rustamm@gmail.com>
 * Date              : 25.03.2021 15:05
 * Last Modified Date: 02.04.2021 21:55
 * Last Modified By  : Rustam Khafizov <super.rustamm@gmail.com>
 */

#ifndef PARSER_HPP
# define PARSER_HPP

# include <boost/program_options.hpp>
# include <iostream>
# include <fstream>
# include <cstdint>
# include <string>

# include "state.hpp"

namespace po = boost::program_options;

class Parser
{
public:
    Parser() {}

    void parse_cmd_options(int argc, char **argv);

    State *generate_initial_state();
    State *generate_final_state();

    std::string get_heuristic();

private:
    std::vector<std::string> puzzle_lines;
    po::variables_map        var_map;
    int64_t                  puzzle_dimension{0};

    void _read_puzzle_file();
};

#endif
