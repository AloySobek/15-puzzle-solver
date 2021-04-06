/**
 * File              : parser.cpp
 * Author            : Rustam Khafizov <super.rustamm@gmail.com>
 * Date              : 02.04.2021 21:29
 * Last Modified Date: 06.04.2021 15:10
 * Last Modified By  : Rustam Khafizov <super.rustamm@gmail.com>
 */

#include "parser.hpp"
#include <stdexcept>

void Parser::parse_cmd_options(int argc, char **argv)
{
    po::options_description options("Allowed options");

    options.add_options()
        ("help,h", "Show help message")
        ("puzzle,p", po::value<std::string>()->required(), "puzzle file")
        ("heuristic,e", po::value<std::string>()->default_value("hamming"),
         "heuristic function");

    po::store(po::parse_command_line(argc, argv, options), var_map);

    if (var_map.count("help"))
        options.print(std::cout, 0), exit(0);

    po::notify(var_map);
}

void Parser::parse_puzzle_file()
{
    std::fstream file;
    std::string line;

    file.open(var_map["puzzle"].as<std::string>());

    while (std::getline(file, line))
    {
        if (line.size() == 0) continue;
        line.erase(std::find(line.begin(), line.end(), '#'), line.end());
        if (line.size() == 0) continue;
        pzl_lines.push_back(line);
    }

    if (!pzl_lines.size())
        throw std::invalid_argument("Empty file!");

    for (int64_t n{0}, i{0}, l{0}; l < (int64_t)pzl_lines.size(); ++l)
    {
        std::istringstream  data(pzl_lines[l]);

        if (!pzl_n)        
        {
            data >> pzl_n;
            if (pzl_n < 2 || pzl_n >= 5 || data >> pzl_n)
                throw std::invalid_argument("Wrong dimension number");
            else if ((int64_t)pzl_lines.size() - 1 != pzl_n)
                throw std::invalid_argument("Wrong dimension rows");
        }
        else
        {
            for (i = 0; i < pzl_n; ++i) data >> n;
            if (i != pzl_n || data >> n)
                throw std::invalid_argument("Wrong numbers in a row");
        }
    }
}

State *Parser::get_initial_state()
{
    State *state{new State()};

    for (uint64_t l{1}; l < pzl_lines.size(); ++l)
    {
        std::vector<int64_t> row;
        std::istringstream   data(pzl_lines[l]);

        for (int64_t i{0}, value; i < pzl_n; ++i)
        {
            data >> value;
            if (!value) state->x = i, state->y = l - 1;
            row.push_back(value);
        }
        state->pzl.push_back(row);
    }
    return (state);
}

State *Parser::get_final_state()
{
    State *state{new State()};
    std::vector<int64_t> row;

    for (int64_t y{0}; y < pzl_n; ++y, row.clear())
    {
        for (int64_t x{0}; x < pzl_n; ++x)
            row.push_back(pzl_n * y + x + 1); 
        state->pzl.push_back(row);
    }
    state->pzl[pzl_n - 1][pzl_n - 1] = 0;
    return (state);
}

State *Parser::_get_final_state()
{
    State *state{new State()};

    switch(pzl_n) {
        case 2:
            state->pzl = {{1, 2}, {0, 3}};
            break;
        case 3:
            state->pzl = {{1, 2, 3}, {8, 0, 4}, {7, 6, 5}};
            break;
        case 4:
            state->pzl = {{1, 2, 3, 4}, {12, 13, 14, 5}, {11, 0, 15, 6}, {10, 9, 8, 7}};
            break;
    }
    return (state);
}

std::string Parser::get_heuristic()
{
    return (var_map["heuristic"].as<std::string>());
}
