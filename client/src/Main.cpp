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
        Core core(parser.getPort(), parser.getMachine());
        core.run();
    } catch (const Parser::ParserException &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}
