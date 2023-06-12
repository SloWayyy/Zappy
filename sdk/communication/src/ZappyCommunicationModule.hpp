/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** SDK
*/

#ifndef ZAPPYCOMMUNICATIONMODULE_HPP_
#define ZAPPYCOMMUNICATIONMODULE_HPP_

#include <string>

#include "ACommunicationModule.hpp"

namespace zappy::sdk {
    class ZappyCommunicationModule : public ACommunicationModule {
        public:
            ZappyCommunicationModule();

            void connectAsGraphical() final;
    };
}

#endif
