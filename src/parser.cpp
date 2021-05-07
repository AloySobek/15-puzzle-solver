/**
 * File              : parser.cpp
 * Author            : Rustam Khafizov <super.rustamm@gmail.com>
 * Date              : 02.04.2021 21:29
 * Last Modified Date: 06.05.2021 00:09
 * Last Modified By  : Rustam Khafizov <super.rustamm@gmail.com>
 */

#include "parser.hpp"
#include <boost/program_options/value_semantic.hpp>

void Parser::parse_cmd_options(int argc, char **argv)
{
    po::options_description options("Allowed options");
    po::positional_options_description positional_options;

    options.add_options()
        ("help", "show help message")
        ("puzzle,p", po::value<std::string>(), "puzzle file")
        ("random,r", po::value<uint64_t>()->default_value(3), "random puzzle")
        ("solution,s", po::value<std::string>()->default_value("snail"),
         "solution pattern")
        ("algorithm,a", po::value<std::string>()->default_value("A*"),
         "solve algorithm")
        ("algo-type,t", po::value<std::string>()->default_value("UCS+GREEDY"),
         "solve algorithm type")
        ("heuristic,h", po::value<std::string>()->default_value("manhattan"),
         "heuristic function");
    positional_options.add("puzzle", -1);

    po::store(po::command_line_parser(argc, argv)
        .positional(positional_options).options(options).run(), var_map);

    if (var_map.count("help")
            || std::find(possible_solution_patterns.begin(),
                possible_solution_patterns.end(),
                var_map["solution"].as<std::string>())
                == possible_solution_patterns.end()
            || std::find(possible_heuristics.begin(),
                possible_heuristics.end(),
                var_map["heuristic"].as<std::string>())
                == possible_heuristics.end()
            || std::find(possible_algorithms.begin(),
                possible_algorithms.end(),
                var_map["algorithm"].as<std::string>())
                == possible_algorithms.end()
            || std::find(possible_algorithm_types.begin(),
                possible_algorithm_types.end(),
                var_map["algo-type"].as<std::string>())
                == possible_algorithm_types.end())
    {
        std::cout << "Usage: n-puzzle [options] [file]\n\n";
        options.print(std::cout, 0), exit(0);
    }
    ProgramState::instance()->heuristic = var_map["heuristic"].as<std::string>();
    ProgramState::instance()->algorithm = var_map["algorithm"].as<std::string>();
    ProgramState::instance()->algo_type = var_map["algo-type"].as<std::string>();
}

State *Parser::get_initial_state()
{
    std::vector<std::string> lines;
    std::ifstream            file;
    std::string              line;

    if (!var_map.count("puzzle"))
        return from_random(var_map["random"].as<uint64_t>());
    file.open(var_map["puzzle"].as<std::string>());
    while (std::getline(file, line))
    {
        if (line.size() == 0) continue;
        line.erase(std::find(line.begin(), line.end(), '#'), line.end());
        if (line.size() == 0) continue;
        lines.push_back(line);
    }
    return (from_lines(lines));
}

const State *Parser::get_final_state()
{
    std::vector<std::string> lines;
    std::ifstream            file;
    std::string              line;
    State                    *final{new State()};

    if (!var_map.count("puzzle"))
        final->size = var_map["random"].as<uint64_t>();
    else
    {
        file.open(var_map["puzzle"].as<std::string>());
        while (std::getline(file, line))
        {
            if (line.size() == 0) continue;
            line.erase(std::find(line.begin(), line.end(), '#'), line.end());
            if (line.size() == 0) continue;
            lines.push_back(line);
        }
        std::istringstream data(lines[0]);
        data >> final->size;
    }

    if (var_map["solution"].as<std::string>() == "snail")
    {
        switch(final->size) {
            case 2:
                final->pzl = {1, 2, 0, 3}; final->zero_position = 2; break;
            case 3:
                final->pzl = {1, 2, 3, 8, 0, 4, 7, 6, 5}; final->zero_position = 4; break;
            case 4:
                final->pzl = {1, 2, 3, 4, 12, 13, 14, 5, 11, 0, 15, 6, 10, 9, 8, 7}; final->zero_position = 9; break;
        }
    }
    else if (var_map["solution"].as<std::string>() == "classic")
    {
        final->zero_position= final->size * final->size - 1;
        switch(final->size) {
            case 2:
                final->pzl = {1, 2, 3, 0}; break;
            case 3:
                final->pzl = {1, 2, 3, 4, 5, 6, 7, 8, 0}; break;
            case 4:
                final->pzl = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0}; break;
        }
    }
    else if (var_map["solution"].as<std::string>() == "first-zero")
    {
        final->zero_position = 0;
        switch(final->size) {
            case 2:
                final->pzl = {0, 1, 2, 3}; break;
            case 3:
                final->pzl = {0, 1, 2, 3, 4, 5, 6, 7, 8}; break;
            case 4:
                final->pzl = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15}; break;
        }
    }
    return (final);
}

const std::string Parser::get_heuristic()
{
    return (var_map["heuristic"].as<std::string>());
}

State *Parser::from_random(uint64_t n)
{
    if (n < 2)
        throw std::invalid_argument("Something wrong with puzzle size");

    int64_t *mem{new int64_t[n * n]()};
    State   *initial{new State()};

    memset(mem, -1, n * n * sizeof(int64_t));
    std::srand(std::time(nullptr));
    initial->size = n;

    for (uint64_t i{0}; i < n*n; ++i)
        for (uint64_t random{std::rand()%(n*n)}; true; random=std::rand()%(n*n))
            if (mem[random] == -1)
            {
                if (!random)
                    initial->zero_position = i;
                initial->pzl.push_back(random);
                mem[random] = random;
                break;
            }
    return (initial);
}

State *Parser::from_lines(std::vector<std::string> &lines)
{
    uint64_t n{0}, i{0};
    int64_t  v{0};
    State    *initial{new State()};

    if (!lines.size())
        throw std::invalid_argument("Empty file!");

    for (uint64_t l{0}; l < lines.size(); ++l)
    {
        std::istringstream  data(lines[l]);

        if (!n)        
        {
            data >> n, initial->size = n;
            if (n < 2 || data >> n)
                throw std::invalid_argument("Something wrong with puzzle size");
            else if (lines.size() - 1 != n)
                throw std::invalid_argument("Wrong number of lines");
        }
        else
        {
            for (i = 0; i < n && data >> v; ++i, initial->pzl.push_back(v))
                if (!v) initial->zero_position = (l - 1) * n + i;
            if (i != n || data >> n)
                throw std::invalid_argument("Wrong number in a row");
        }
    }
    return (initial);
}
