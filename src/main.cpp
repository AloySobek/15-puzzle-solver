/**
 * File              : main.cpp
 * Author            : Rustam Khafizov <super.rustamm@gmail.com>
 * Date              : 25.03.2021 13:28
 * Last Modified Date: 29.03.2021 00:46
 * Last Modified By  : Rustam Khafizov <super.rustamm@gmail.com>
 */

#include <exception>
#include <cstdint>

#include "../include/parser.hpp"
#include "../include/graph.hpp"

int main(int argc, char **argv)
{
    Parser *parser = new Parser();
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

    State *initial_state = new State();
    initial_state->puzzle = parser->puzzle;
    Node<State *, int32_t> *initial_node = new Node<State *, int32_t>(initial_state);
    Node<State *, int32_t> *another_node = new Node<State *, int32_t>(initial_state);
    Node<State *, int32_t>::Edge *initial_to_another = new Node<State *, int32_t>::Edge();
    initial_to_another->endpoint = another_node;
    initial_node->edges.push_back(initial_to_another);

    for (int i{0}; i < initial_node->content->puzzle.size(); ++i)
    {
        for (int n{0}; n < initial_node->content->puzzle[i].size(); ++n)
            std::cout << initial_node->content->puzzle[i][n] << " ";
        std::cout << std::endl;
    }

    for (Node<State *, int32_t>::Edge *edge : initial_node->edges)
    {
        for (int i{0}; i < edge->endpoint->content->puzzle.size(); ++i)
        {
            for (int n{0}; n < edge->endpoint->content->puzzle[i].size(); ++n)
                std::cout << edge->endpoint->content->puzzle[i][n] << " ";
            std::cout << std::endl;
        }      
    }
    
    return (0);
}
