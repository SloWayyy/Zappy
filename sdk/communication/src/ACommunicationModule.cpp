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
#define MAX_BUFFER_SIZE 512
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

std::string zappy::sdk::ACommunicationModule::readBuffer() {
    char buffer[MAX_BUFFER_SIZE];
    this->_readBuffer.clear();

    FD_ZERO(&this->reads_set);
    FD_SET(this->_socketFd, &this->reads_set);
    FD_ZERO(&this->writes_set);
    FD_SET(this->_socketFd, &this->writes_set);
    if (select(this->_socketFd + 1, &this->reads_set, &this->writes_set, nullptr, nullptr) == -1) {
        throw CommunicationException("select failed");
    }
    if (FD_ISSET(this->_socketFd, &this->reads_set)) {
        if (read(this->_socketFd, buffer, MAX_BUFFER_SIZE) == -1) {
            return "";
        }
        this->_readBuffer = buffer;
        if (this->_readBuffer.find('\n') == std::string::npos) {
            this->_tmp = this->_readBuffer;
            this->_readBuffer.clear();
        } else {
            this->_readBuffer = this->_tmp + this->_readBuffer;
            this->_tmp.clear();
        }
    }
    if (!this->_writeBuffer.empty()) {
        write(this->_socketFd, this->_writeBuffer.c_str(), this->_writeBuffer.size());
        this->_writeBuffer.clear();
    }
    return this->_readBuffer;
}

int zappy::sdk::ACommunicationModule::getSocketFd() const {
    return this->_socketFd;
}