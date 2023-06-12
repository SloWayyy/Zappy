/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** SDK
*/

#include "ZappyCommunicationModule.hpp"
#include <unistd.h>

zappy::sdk::ZappyCommunicationModule::ZappyCommunicationModule(): ACommunicationModule() {

}

void zappy::sdk::ZappyCommunicationModule::connectAsGraphical() {
    write(this->getSocketFd(), "GRAPHIC\n", 8);
}
