/**
 * File              : parser.hpp
 * Author            : Rustam Khafizov <super.rustamm@gmail.com>
 * Date              : 25.03.2021 15:05
 * Last Modified Date: 01.04.2021 23:09
 * Last Modified By  : Rustam Khafizov <super.rustamm@gmail.com>
 */

#ifndef PARSER_HPP
# define PARSER_HPP

# include <boost/program_options.hpp>
# include <iostream>
# include <fstream>
# include <cstdint>
# include <string>

# include "graph.hpp"

namespace po = boost::program_options;

class Parser
{
public:
    Parser() {}

    void parse_cmd_options(int argc, char **argv)
    {
        po::options_description options("Allowed options");

        options.add_options()
            ("help,h", "Show help message")
            ("puzzle,p", po::value<std::string>()->required(), "puzzle file")
            ("heuristic,e", po::value<std::string>()->default_value("hamming"), "heuristic function");

        po::store(po::parse_command_line(argc, argv, options), var_map);

        if (var_map.count("help"))
            options.print(std::cout, 0), exit(0);

        po::notify(var_map);
    }

    State *generate_initial_state()
    {
        std::vector<std::vector<int64_t>> puzzle;
        State *initial_state{new State()};

        _read_puzzle_file();
        
        for (std::vector<std::string>::size_type l{0}; l < puzzle_lines.size(); ++l)
        {
            std::istringstream  data(puzzle_lines[l]);

            if (!puzzle_dimension)
            {
                data >> puzzle_dimension;
                if (puzzle_dimension < 2 || puzzle_dimension >= 100)
                    throw std::invalid_argument("Puzzle too small or too big");
                if (data >> puzzle_dimension)
                    throw std::invalid_argument("Puzzle dimension is just ONE NUMBER"); 
            }
            else
            {
                std::vector<int64_t> row;

                for (int32_t i{0}, value; i < puzzle_dimension; ++i)
                {
                    data >> value;
                    if (value == 0)
                        initial_state->x = i, initial_state->y = l - 1;
                    row.push_back(value);
                }
                puzzle.push_back(row);
            }
        }
        initial_state->puzzle = puzzle;
        return (initial_state);
    }

    State *generate_final_state()
    {
        std::vector<std::vector<int64_t>> final_puzzle;
        State *final_state{new State()};
        std::vector<int64_t> row;

        for (int64_t y{0}; y < puzzle_dimension; ++y)
        {
            for (int64_t x{0}; x < puzzle_dimension; ++x)
                row.push_back(puzzle_dimension * y + x + 1); 
            final_puzzle.push_back(row);
            row.clear();
        }

        final_puzzle[puzzle_dimension - 1][puzzle_dimension -1] = 0;
        final_state->puzzle = final_puzzle;

        return (final_state);
    }

    std::string get_heuristic() { return (var_map["heuristic"].as<std::string>()); }

private:
    std::vector<std::string> puzzle_lines;
    po::variables_map        var_map;
    int64_t                  puzzle_dimension{0};

    void _read_puzzle_file()
    {
        std::fstream file;
        std::string  line;

        file.open(var_map["puzzle"].as<std::string>());

        while (std::getline(file, line))
        {
            if (line.size() == 0) continue;
            line.erase(std::find( line.begin(), line.end(), '#' ), line.end());
            if (line.size() == 0) continue;
            puzzle_lines.push_back(line);
        }
    }
};

#endif
