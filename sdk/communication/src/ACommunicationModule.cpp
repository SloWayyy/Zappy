/*
** EPITECH PROJECT, 2023
** communication
** File description:
** ACommunicationModule.cpp
*/

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include "ACommunicationModule.hpp"

void zappy::sdk::ACommunicationModule::connect(const std::string &host, int port) {
    struct sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(host.c_str());

    auto *addr_ptr = (struct sockaddr *)&addr;

    this->_socketFd = socket(AF_INET, SOCK_STREAM, 0);
    if (this->_socketFd == -1) {
        throw CommunicationException("socket failed");
    }
    if (::connect(this->_socketFd, addr_ptr, sizeof(addr)) == -1) {
        throw CommunicationException("connect failed");
    }
    this->_stream = __gnu_cxx::stdio_filebuf<char>(this->_socketFd, std::ios_base::in | std::ios_base::out);
}

void zappy::sdk::ACommunicationModule::disconnect() {
    close(this->_socketFd);
}

bool zappy::sdk::ACommunicationModule::isConnected() {
    return this->_stream.is_open();
}

bool zappy::sdk::ACommunicationModule::dumpBuffers() {
    bool exit = false;
    int res = 0;
    std::string line;
    struct timeval timeout = { 0, 1 };
    this->_readBuffer.clear();

    while (!exit) {
        FD_ZERO(&this->reads_set);
        FD_ZERO(&this->writes_set);
        FD_SET(this->_socketFd, &this->reads_set);
        if (!this->_writeBuffer.empty()) {
            FD_SET(this->_socketFd, &this->writes_set);
        }
        res = select(this->_socketFd + 1, &this->reads_set, &this->writes_set, nullptr, &timeout);
        if (res == -1) {
            throw CommunicationException("select failed");
        }
        if (FD_ISSET(this->_socketFd, &this->reads_set)) {
            std::istream is(&this->_stream);
            if (!std::getline(is, line)) {
                this->disconnect();
                return false;
            }
            this->_readBuffer += line;
            std::cout << line << std::endl;
        }
        if (!this->_writeBuffer.empty()) {
            std::ostream os(&this->_stream);
            os << this->_writeBuffer;
            this->_writeBuffer.clear();
        }
        exit = res == 0;
    }
    return true;
}

int zappy::sdk::ACommunicationModule::getSocketFd() const {
    return this->_socketFd;
}