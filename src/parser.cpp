/**
 * File              : parser.cpp
 * Author            : Rustam Khafizov <super.rustamm@gmail.com>
 * Date              : 02.04.2021 21:29
 * Last Modified Date: 09.04.2021 23:53
 * Last Modified By  : Rustam Khafizov <super.rustamm@gmail.com>
 */

#include "parser.hpp"

void Parser::parse_cmd_options(int argc, char **argv)
{
    po::options_description options("Allowed options");

    options.add_options()
        ("help,h", "Show help message")
        ("puzzle,p", po::value<std::string>()->required(), "puzzle file")
        ("solution,s", po::value<std::string>()->default_value("snail"),
         "solution pattern")
        ("heuristic,e", po::value<std::string>()->default_value("manhattan"),
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

const State *Parser::get_final_state()
{
    State *state{new State()};

    if (var_map["solution"].as<std::string>() == "snail")
    {
        switch(pzl_n) {
            case 2:
                state->pzl = {{1, 2}, {0, 3}};
                state->x = 0, state->y = 1;
                break;
            case 3:
                state->pzl = {{1, 2, 3}, {8, 0, 4}, {7, 6, 5}};
                state->x = 1, state->y = 1;
                break;
            case 4:
                state->pzl = {{1, 2, 3, 4}, {12, 13, 14, 5}, {11, 0, 15, 6}, {10, 9, 8, 7}};
                state->x = 1, state->y = 2;
                break;
        }
    }
    else if (var_map["solution"].as<std::string>() == "classic")
    {
        switch(pzl_n) {
            case 2:
                state->pzl = {{1, 2}, {3, 0}};
                state->x = 1, state->y = 1;
                break;
            case 3:
                state->pzl = {{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};
                state->x = 2, state->y = 2;
                break;
            case 4:
                state->pzl = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 0}};
                state->x = 3, state->y = 3;
                break;
        }
    }
    return (state);
}

const std::string Parser::get_heuristic()
{
    return (var_map["heuristic"].as<std::string>());
}
