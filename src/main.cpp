/**
 * File              : main.cpp
 * Author            : Rustam Khafizov <super.rustamm@gmail.com>
 * Date              : 25.03.2021 13:28
 * Last Modified Date: 03.04.2021 18:30
 * Last Modified By  : Rustam Khafizov <super.rustamm@gmail.com>
 */

#include <sys/resource.h>
#include <exception>
#include <cstdint>

#include "state.hpp"
#include "parser.hpp"
#include "solver.hpp"

int main(int argc, char **argv)
{
    Parser *parser{new Parser()};
    Solver *solver{new Solver()};

    try
    {
        parser->parse_cmd_options(argc , argv);
        parser->parse_puzzle_file();
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
        return (-1);
    }

    try
    {
        if (solver->is_solvable(parser->get_initial_state()))
            solver->solve(parser->get_final_state(),
                    parser->get_initial_state(), parser->get_heuristic());
        else
            std::cout << "Sorry, your puzzle is not solvable!" << std::endl;
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
        return (-1);
    }

    delete parser;
    delete solver;

    return (0);
}
