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
