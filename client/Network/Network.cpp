/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** network.cpp
*/

#include "Network.hpp"

Network::Network(int port, std::string ip)
{
    this->_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (this->_socket == -1)
        throw NetworkException("Error creating socket");
    _host = gethostbyname(ip.c_str());
    if (_host == NULL)
        throw NetworkException("Error getting host");
    this->_server.sin_addr.s_addr = inet_addr(ip.c_str());
    this->_server.sin_family = AF_INET;
    this->_server.sin_port = htons(port);
}

Network::~Network()
{
}

void Network::connectToServer()
{
    if (connect(this->_socket, (struct sockaddr *)&this->_server, sizeof(this->_server)) < 0)
        throw NetworkException("Connection failed");
}

void Network::set_fd()
{
    FD_ZERO(&this->_readfds);
    FD_SET(this->_socket, &this->_readfds);
    FD_SET(0, &this->_readfds);
}

void Network::select_socket()
{
    timeval timeout;
    timeout.tv_sec = 0;
    timeout.tv_usec = 1;
    if (select(this->_socket + 1, &this->_readfds, NULL, NULL, &timeout) < 0)
        throw Network::NetworkException("Select failed");
}

void Network::GetresponseFromServer()
{
    if (FD_ISSET(this->_socket, &this->_readfds)) {
        char buffer[1024] = {0};
        int valread = read(this->_socket, buffer, 1024);
        if (valread <= 0) {
            throw Network::NetworkException("Server disconnected");
        }
        std::cout << buffer;
        this->_buffer = buffer;
    }
}

fd_set &Network::getReadfds()
{
    return this->_readfds;
}

void Network::closeConnection()
{
    close(this->_socket);
}

int Network::getSocket() const
{
    return this->_socket;
}

void Network::setSocket(int socket)
{
    this->_socket = socket;
}

std::string &Network::getBuffer()
{
    return this->_buffer;
}

void Network::setBuffer(std::string buffer)
{
    this->_buffer = buffer;
}

Network::NetworkException::NetworkException(std::string const &message) : _message(message)
{
}

const char *Network::NetworkException::what() const noexcept
{
    return this->_message.c_str();
}
