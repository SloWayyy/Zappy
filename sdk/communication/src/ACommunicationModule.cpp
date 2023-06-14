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
}

void zappy::sdk::ACommunicationModule::disconnect() {
    close(this->_socketFd);
}

bool zappy::sdk::ACommunicationModule::isConnected() {
    return this->_stream.is_open();
}

std::vector<std::string> zappy::sdk::ACommunicationModule::readBuffer() {
    char buffer[MAX_BUFFER_SIZE];
    this->_tmp.clear();
    std::vector<std::string> queuecommand;
    std::string tempo;

    FD_ZERO(&this->reads_set);
    FD_SET(this->_socketFd, &this->reads_set);
    FD_ZERO(&this->writes_set);
    FD_SET(this->_socketFd, &this->writes_set);
    if (select(this->_socketFd + 1, &this->reads_set, &this->writes_set, nullptr, nullptr) == -1) {
        throw CommunicationException("select failed");
    }
    if (FD_ISSET(this->_socketFd, &this->reads_set)) {
        if (read(this->_socketFd, buffer, MAX_BUFFER_SIZE) <= 0) {
            return queuecommand;
        }
        this->_readBuffer = this->_saveNextBuffer + buffer;
        this->_tmp = this->_readBuffer.substr(0, this->_readBuffer.find_last_of('\n') + 1);
        this->_saveNextBuffer = this->_readBuffer.substr(this->_readBuffer.find_last_of('\n') + 1);
        if (this->_saveNextBuffer.empty()) {
            this->_readBuffer.clear();
        }
    }
    if (!this->_writeBuffer.empty()) {
        write(this->_socketFd, this->_writeBuffer.c_str(), this->_writeBuffer.size());
        this->_writeBuffer.clear();
    }
    tempo = this->_tmp;
    while (!tempo.empty()) {
        queuecommand.push_back(tempo.substr(0, tempo.find_first_of('\n')));
        tempo = tempo.substr(tempo.find_first_of('\n') + 1);
    }
    return queuecommand;
}

int zappy::sdk::ACommunicationModule::getSocketFd() const {
    return this->_socketFd;
}