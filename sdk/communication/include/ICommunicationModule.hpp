/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Shared interface
*/

#ifndef ICOMMUNICATIONMODULE_HPP_
#define ICOMMUNICATIONMODULE_HPP_

#include <exception>
#include <string>
#include <utility>

namespace zappy::sdk {
    class CommunicationException : std::exception {
        public:
            explicit CommunicationException(std::string message);

            [[nodiscard]] const char *what() const noexcept override;

        private:
            std::string _message;
    };

    class ICommunicationModule {
        public:
            virtual ~ICommunicationModule() = default;

            virtual void connect(const std::string &host, int port) = 0;
            virtual void connectAsGraphical() = 0;
            virtual void disconnect() = 0;
            virtual bool isConnected() = 0;
    };
}

extern "C" zappy::sdk::ICommunicationModule *communicationEntrypoint();

#endif
