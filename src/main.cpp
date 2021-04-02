/**
 * File              : main.cpp
 * Author            : Rustam Khafizov <super.rustamm@gmail.com>
 * Date              : 25.03.2021 13:28
 * Last Modified Date: 03.04.2021 00:40
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

    State *initial_state;
    State *final_state; 

    try
    {
        parser->parse_cmd_options(argc , argv);
        initial_state = parser->generate_initial_state();
        final_state = parser->generate_final_state();
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
        return (-1);
    }

    initial_state->print(), std::cout << std::endl;

    if (solver->is_solvable(initial_state))
    {
        std::cout << "Solvable" << std::endl;
        solver->solve(final_state, initial_state, parser->get_heuristic());
    }
    else
        std::cout << "Sorry, your puzzle is not solvable at all!" << std::endl;

    delete parser;
    delete solver;

    return (0);
}
