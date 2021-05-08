/**
 * File              : main.cpp
 * Author            : Rustam Khafizov <super.rustamm@gmail.com>
 * Date              : 03.05.2021 17:49
 * Last Modified Date: 08.05.2021 22:39
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

void  print_solved(const State *s, uint64_t *moves)
{
    if (!s)
        return ;
    ++(*moves);
    print_solved(s->parent, moves);
    std::cout << "       " << s->to_string() << std::endl;
}

int main(int argc, char **argv)
{
    const State  *final{nullptr};
    uint64_t     moves{0};
    Parser       *parser{new Parser()};
    Solver       *solver{new Solver()};
    State        *solved{nullptr};
    State        *initial{nullptr};

    try
    {
        parser->parse_cmd_options(argc, argv);
        initial = parser->get_initial_state();
        final = parser->get_final_state();
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
        return (-1);
    }

    std::cout << "Initial state      Final state" << "\n\n";
    for (uint64_t i{0}; i < final->size; ++i)
        std::cout << "    " << initial->row_to_string(i) << "            "
            << final->row_to_string(i) << std::endl;
    std::cout << std::endl;
    if (solver->is_solvable(initial, final))
        solved = solver->solve(initial, final);
    else
        std::cout << "Sorry, this puzzle is not solvable!" << std::endl;
    print_solved(solved, &moves);
    std::cout << std::endl;
    std::cout << "    Total amount of moves: " << moves << std::endl;
    std::cout << std::endl;
    std::cout << "     Complexity in time: " << ProgramState::instance()->visited_nodes << std::endl;
    std::cout << "     Complexity in size: " << ProgramState::instance()->expanded_nodes << std::endl;

    delete parser;
    delete solver;

    ProgramState::destroy();
    exit(0);
}
