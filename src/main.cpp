/**
 * File              : main.cpp
 * Author            : Rustam Khafizov <super.rustamm@gmail.com>
 * Date              : 03.05.2021 17:49
 * Last Modified Date: 06.05.2021 00:06
 * Last Modified By  : Rustam Khafizov <super.rustamm@gmail.com>
 */

#include <sys/resource.h>
#include <exception>
#include <cstdint>
#include <cmath>

#include "state.hpp"
#include "parser.hpp"
#include "solver.hpp"

#include "program-state.hpp"

void print_result(const State *s)
{
    if (!s)
        return;
    print_result(s->parent);
    std::cout << s->to_string() << std::endl;
}

int main(int argc, char **argv)
{
    Parser *parser{new Parser()};
    Solver *solver{new Solver()};

    parser->parse_cmd_options(argc, argv);

    State *initial = parser->get_initial_state();
    const State *final = parser->get_final_state();

    std::cout << "Initial state: " << initial->to_string() << std::endl;
    std::cout << "Final state:   " << final->to_string() << std::endl;

    if (solver->is_solvable(initial, final))
        print_result(solver->solve(initial, final));
    else
        std::cout << "Sorry, your puzzle is not solvable!" << std::endl;

    delete parser;
    delete solver;

    ProgramState::destroy();

    return (0);
}
