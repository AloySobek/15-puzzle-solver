/**
 * File              : main.cpp
 * Author            : Rustam Khafizov <super.rustamm@gmail.com>
 * Date              : 25.03.2021 13:28
 * Last Modified Date: 30.03.2021 00:07
 * Last Modified By  : Rustam Khafizov <super.rustamm@gmail.com>
 */

#include <exception>
#include <cstdint>

#include "../include/parser.hpp"
#include "../include/solver.hpp"
#include "../include/graph.hpp"

int main(int argc, char **argv)
{
    Parser *parser = new Parser();
    Solver *solver = new Solver();

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

    Node<State, int32_t> *initial_node = new Node<State, int32_t>
        (new State(parser->puzzle));

    try
    {
        /* solver->check_if_solvable(initial_node); */
        solver->solve(initial_node);
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
        return (-1);
    }

    return (0);
}
