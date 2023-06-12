/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Parser.cpp
*/

#include "Parser.hpp"

Parser::ParserException::ParserException(std::string const &message) : _message(message)
{
}

const char *Parser::ParserException::what() const noexcept
{
    return this->_message.c_str();
}

Parser::Parser(int ac, char **av)
{
    this->setHelp();
    if (ac != 5)
        throw ParserException("Invalid number of arguments\n" + this->_usage);
    for (int i = 0; i < ac; i++)
        this->_av.push_back(av[i]);
}

size_t Parser::getPort(void) const
{
    return this->_port;
}

std::string Parser::getMachine(void) const
{
    return this->machine;
}

void Parser::setHelp(void)
{
    this->_usage = "USAGE: ./zappy_ai -p port -n name -h machine\n";
    this->_usage += "\tport\tis the port number\n";
    this->_usage += "\tmachine\tis the name of the machine; localhost by default\n";
}

void Parser::handleArgs(void)
{
    if (this->_av[1].compare("-p") != 0 || this->_av[3].compare("-h") != 0)
        throw ParserException("Invalid flag\n" + this->_usage);
    this->_port = this->parseArgs<size_t>(this->_av[2]);
    this->machine = this->_av[4];
    if (this->_port < 1 || this->_port > 65535)
        throw ParserException("Invalid port\n" + this->_usage);
}
