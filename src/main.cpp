/**
 * File              : main.cpp
 * Author            : Rustam Khafizov <super.rustamm@gmail.com>
 * Date              : 25.03.2021 13:28
 * Last Modified Date: 02.04.2021 14:41
 * Last Modified By  : Rustam Khafizov <super.rustamm@gmail.com>
 */

#include <sys/resource.h>
#include <exception>
#include <cstdint>

#include "parser.hpp"
#include "solver.hpp"
#include "graph.hpp"

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

    initial_state->print();

    std::cout << std::endl;

    try
    {
        solver->check_if_solvable(initial_state);
        solver->solve(final_state, initial_state, parser->get_heuristic());
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
        return (-1);
    }

    return (0);
}
