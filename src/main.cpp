/**
 * File              : main.cpp
 * Author            : Rustam Khafizov <super.rustamm@gmail.com>
 * Date              : 03.05.2021 17:49
 * Last Modified Date: 08.05.2021 18:11
 * Last Modified By  : Rustam Khafizov <super.rustamm@gmail.com>
 */

#include <sys/resource.h>
#include <exception>
#include <ncurses.h>
#include <cstdint>
#include <cmath>

#include "state.hpp"
#include "parser.hpp"
#include "solver.hpp"

#include "program-state.hpp"

void print_solved(const State *s)
{
    if (!s)
        return;
    print_solved(s->parent);
    std::cout << s->to_string() << std::endl;
}

int main(int argc, char **argv)
{
    Parser *parser{new Parser()};
    Solver *solver{new Solver()};

    parser->parse_cmd_options(argc, argv);

    State *initial = parser->get_initial_state();
    const State *final = parser->get_final_state();
    State *solved{nullptr};

    std::cout << "Initial state: " << initial->to_string() << std::endl;
    std::cout << "Final state: " << final->to_string() << std::endl;

    if (solver->is_solvable(initial, final))
        solved = solver->solve(initial, final);
    else
        std::cout << "Sorry, this puzzle is not solvable!" << std::endl;

    print_solved(solved);

    std::cout << "Visited nodes: " << ProgramState::instance()->visited_nodes << std::endl;
    std::cout << "Expanded nodes: " << ProgramState::instance()->expanded_nodes << std::endl;

    delete parser;
    delete solver;

    ProgramState::destroy();

    return (0);
}
