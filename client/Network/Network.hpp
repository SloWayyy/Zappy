/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** network.hpp
*/

#ifndef NETWORK_HPP_
    #define NETWORK_HPP_

    #include <iostream>
    #include <string>
    #include <sys/socket.h>
    #include <arpa/inet.h>
    #include <netdb.h>
    #include <unistd.h>

class Network {
    public:
        Network(int port, std::string ip);
        ~Network();
        void connectToServer();
        void closeConnection();
        int getSocket() const;
        void setSocket(int socket);
        std::string &getBuffer();
        void setBuffer(std::string buffer);
        void set_fd();
        void select_socket();
        fd_set &getReadfds();
        void GetresponseFromServer();
        class NetworkException : public std::exception {
            public:
                NetworkException(std::string const &message);
                ~NetworkException() = default;
                const char *what() const noexcept;
            private:
                std::string _message;
        };
    private:
        int _socket;
        struct sockaddr_in _server;
        struct hostent *_host;
        std::string _buffer;
        fd_set _readfds;
};

#endif