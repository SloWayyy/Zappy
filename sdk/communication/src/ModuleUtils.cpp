/*
** EPITECH PROJECT, 2023
** communication
** File description:
** ICommunicationModule.cpp
*/

#include <string>
#include <utility>

#include "ZappyCommunicationModule.hpp"
#include "ICommunicationModule.hpp"

zappy::sdk::ICommunicationModule *communicationEntrypoint() {
    return new zappy::sdk::ZappyCommunicationModule();
}

zappy::sdk::CommunicationException::CommunicationException(std::string message): _message(std::move(message)) {

}

const char *zappy::sdk::CommunicationException::what() const noexcept {
    return this->_message.c_str();
}
