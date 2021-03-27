/**
 * File              : parser.hpp
 * Author            : Rustam Khafizov <super.rustamm@gmail.com>
 * Date              : 25.03.2021 15:05
 * Last Modified Date: 28.03.2021 01:08
 * Last Modified By  : Rustam Khafizov <super.rustamm@gmail.com>
 */

#ifndef PARSER_HPP
# define PARSER_HPP


# include <exception>
# include <iostream>
# include <stdlib.h>
# include <fstream>
# include <cstdint>
# include <string>
# include <boost/program_options.hpp>

namespace po = boost::program_options;

class Parser
{
public:
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
        try
        {
            po::store(po::parse_command_line(argc, argv, cmd_line_options), var_map);

            if (var_map.count("help"))
            {
                cmd_line_options.print(std::cout, 0), exit(0);
            }
            if (var_map.count("version"))
            {
                std::cout << "1.0.0." << std::endl, exit(0);
            }
            po::notify(var_map);
        }
        catch (std::exception &e)
        {
            std::cout << e.what() << std::endl;
        }
    }

    void parse_puzzle_file()
    {
        std::fstream file;
        std::string  filename;
        std::string  line("");
        size_t       file_size;
        bool         inside_comment;
        int32_t      dimension;

        filename = var_map["puzzle-file"].as<std::string>();
        file.open(filename, std::ifstream::ate | std::ifstream::binary);
        file_size = file.tellg();
        buffer = new char[file_size + 1];
        file.read(buffer, file_size);

        inside_comment = false;

        dimension = 0;

        for (int32_t i; i < file_size; ++i)
        {
            if (!inside_comment && buffer[i] == '#')
            {
                inside_comment = true;
            }
            else if (inside_comment)
            {
                if (buffer[i] == '\n')
                {
                    inside_comment = false;
                }
            }
            else
            {
                line.append(buffer + i); 
                if (buffer[i] == '\n')
                {
                    if (!dimension)
                    {
                        dimension = atoi(line.c_str());
                    }
                    else
                    {
                        // Stub
                    }
                }
            }
        }
    }

    ~Parser() {}

private:
    po::options_description cmd_line_options;
    po::options_description general;
    po::options_description algorithm;
    po::variables_map       var_map;
    char                    *buffer;
};

#endif
