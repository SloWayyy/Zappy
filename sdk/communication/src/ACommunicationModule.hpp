/*
** EPITECH PROJECT, 2023
** communication
** File description:
** ACommunicationModule.hpp
*/

#ifndef ACOMMUNICATIONMODULE_HPP_
#define ACOMMUNICATIONMODULE_HPP_

#include <ext/stdio_filebuf.h>
#include <istream>
#include <ostream>
#include <string>
#include <vector>
#include "ICommunicationModule.hpp"

#include <iostream>

namespace zappy::sdk {
    class ACommunicationModule : public ICommunicationModule {
        public:
            ~ACommunicationModule() {
                
            }

        protected:
            void connect(const std::string &host, int port) final;
            void disconnect() final;
            bool isConnected() final;
            std::vector<std::string> readBuffer();
            void writeBuffer(const std::string &command);
            int getSocketFd() const;
            void setDisconnected(bool disconnected);
            bool isDisconnected() const;
            std::string _readBuffer;
            std::string _writeBuffer;
            std::string _tmp;
            std::string _saveNextBuffer;
        private:
            int _socketFd;
            __gnu_cxx::stdio_filebuf<char> _stream;
            fd_set reads_set;
            fd_set writes_set;
            bool disconneted = true;
    };
}

#endif
