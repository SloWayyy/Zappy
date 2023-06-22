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
    this->_port = 0;
    this->machine = "127.0.0.1";
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
    this->_usage = "USAGE: ./zappy_gui -p port -h machine\n";
    this->_usage += "\tport\tis the port number\n";
    this->_usage += "\tmachine\tis the name of the machine\n";
}

void Parser::handleArgs(void)
{
    for (size_t i = 1; i < this->_av.size() - 1; i++) {
        if (this->_av[i] == "-p")
            this->_port = this->parseArgs<size_t>(this->_av[i + 1]);
        else if (this->_av[i] == "-h")
            this->machine = this->_av[i + 1];
        else
            throw ParserException("Invalid argument\n" + this->_usage);
        i++;
    }
    if (this->_port < 1 || this->_port > 65535)
        throw ParserException("Invalid port or missing port argument\n" + this->_usage);
}
