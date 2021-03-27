/**
 * File              : main.cpp
 * Author            : Rustam Khafizov <super.rustamm@gmail.com>
 * Date              : 25.03.2021 13:28
 * Last Modified Date: 26.03.2021 18:58
 * Last Modified By  : Rustam Khafizov <super.rustamm@gmail.com>
 */

#include "../include/parser.hpp"

int main(int argc, char **argv)
{
    Parser *parser = new Parser();

    parser->parse_cmd_options(argc , argv);
    
    return (0);
}
