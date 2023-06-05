/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Main
*/

#include <memory>
#include "encapsulation/Raylibcpp.hpp"
#include "src/Core/Core.hpp"
#include "src/Parser/Parser.hpp"

int main(int ac, char **av)
{
    try {
        Parser parser(ac, av);
        parser.handleArgs();
    } catch (const Parser::ParserException &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    Core core = Core();
    core.run();
    return 0;
}
