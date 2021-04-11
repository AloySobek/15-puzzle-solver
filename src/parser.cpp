/**
 * File              : parser.cpp
 * Author            : Rustam Khafizov <super.rustamm@gmail.com>
 * Date              : 02.04.2021 21:29
 * Last Modified Date: 11.04.2021 20:00
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
    if (std::find(possible_solution_patterns.begin(), possible_solution_patterns.end(), var_map["solution"].as<std::string>()) == possible_solution_patterns.end()) 
        options.print(std::cout, 0), exit(0);
    if (std::find(possible_heuristics.begin(), possible_heuristics.end(), var_map["heuristic"].as<std::string>()) == possible_heuristics.end()) 
        options.print(std::cout, 0), exit(0);

    po::notify(var_map);
}

void Parser::parse_puzzle_file()
{
    std::fstream file;
    std::string  line;
    uint64_t     n{0}, i{0};
    int64_t      tmp{0};

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

    for (uint64_t l{0}; l < pzl_lines.size(); ++l)
    {
        std::istringstream  data(pzl_lines[l]);

        if (!n)        
        {
            data >> n;
            if (n < 2 || n > 5 || data >> n)
                throw std::invalid_argument("Wrong size value");
            else if (pzl_lines.size() - 1 != n)
                throw std::invalid_argument("Wrong number of lines");
        }
        else
        {
            for (i = 0; i < n; ++i)
                data >> tmp;
            if (i != n || data >> n)
                throw std::invalid_argument("Wrong number in a row");
        }
    }
}

State *Parser::get_initial_state()
{
    State *state{new State()};
    int64_t v{0};
    uint64_t n{0};

    for (uint64_t l{0}; l < pzl_lines.size(); ++l)
    {
        std::istringstream data(pzl_lines[l]);

        if (!n)
            data >> n, state->n = n;    
        else
            for (uint64_t i{0}; i < n && data >> v; ++i, state->pzl.push_back(v))
                if (!v) state->i = (l - 1) * n + i;
    }
    return (state);
}

const State *Parser::get_final_state()
{
    std::istringstream data(pzl_lines[0]);
    State *state{new State()};
    uint64_t n{0};

    data >> n;

    if (var_map["solution"].as<std::string>() == "snail")
    {
        switch(n) {
            case 2:
                state->pzl = {1, 2, 0, 3};
                state->i = 2, state->n = 2;
                break;
            case 3:
                state->pzl = {1, 2, 3, 8, 0, 4, 7, 6, 5};
                state->i = 4, state->n = 3;
                break;
            case 4:
                state->pzl = {1, 2, 3, 4, 12, 13, 14, 5, 11, 0, 15, 6, 10, 9, 8, 7};
                state->i = 9, state->n = 4;
                break;
        }
    }
    else if (var_map["solution"].as<std::string>() == "classic")
    {
        switch(n) {
            case 2:
                state->pzl = {1, 2, 3, 0};
                state->i = 3, state->n = 2;
                break;
            case 3:
                state->pzl = {1, 2, 3, 4, 5, 6, 7, 8, 0};
                state->i = 8, state->n = 3;
                break;
            case 4:
                state->pzl = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0};
                state->i = 15, state->n = 4;
                break;
        }
    }
    return (state);
}

const std::string Parser::get_heuristic()
{
    return (var_map["heuristic"].as<std::string>());
}
