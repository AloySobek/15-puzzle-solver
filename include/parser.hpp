/**
 * File              : parser.hpp
 * Author            : Rustam Khafizov <super.rustamm@gmail.com>
 * Date              : 25.03.2021 15:05
 * Last Modified Date: 28.03.2021 23:47
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

namespace po = boost::program_options;

class Parser
{
public:
    std::vector<std::vector<int32_t>>   puzzle;

    Parser()
        : cmd_line_options{po::options_description("Allowed optinos")},
          general{po::options_description("General options")},
          algorithm{po::options_description("Algorithm options")}
    {
        general.add_options()
            ("help,h", "Show help message")
            ("puzzle-file,p", po::value<std::string>()->required(), "The file in which the puzzle store")
            ("version,v", "print version and exit");
        algorithm.add_options()
            ("heuristic,e", po::value<std::string>()->default_value("g"), "A* heuristic functions");
        cmd_line_options.add(general).add(algorithm);
    }

    void parse_cmd_options(int argc, char **argv)
    {
        po::store(po::parse_command_line(argc, argv, cmd_line_options), var_map);
        if (var_map.count("help"))
            cmd_line_options.print(std::cout, 0), exit(0);
        if (var_map.count("version"))
            std::cout << "1.0.0." << std::endl, exit(0);
        po::notify(var_map);
    }

    void parse_puzzle_file()
    {
        std::vector<std::string>    lines;
        std::fstream                file;
        std::string                 line;
        int32_t                     size{0};

        file.open(var_map["puzzle-file"].as<std::string>());
        while (std::getline(file, line))
        {
            if (line.size() == 0) continue;
            line.erase(std::find( line.begin(), line.end(), '#' ), line.end());
            if (line.size() == 0) continue;
            lines.push_back(line);
        }
        for (int32_t l{0}; l < lines.size(); ++l)
        {
            std::istringstream  data(lines[l]);

            if (!size)
            {
                data >> size;
                if (size < 2 || size >= 100)
                    throw std::invalid_argument("Puzzle too small or too big");
                if (data >> size)
                    throw std::invalid_argument("Puzzle dimension is just ONE NUMBER"); 
            }
            else
            {
                std::vector<int32_t> row;
                for (int32_t i{0}, value; i < size; ++i)
                    data >> value, row.push_back(value);
                puzzle.push_back(row);
            }
        }
    }

    ~Parser() {}

private:
    po::options_description cmd_line_options;
    po::options_description general;
    po::options_description algorithm;
    po::variables_map       var_map;
};

#endif
