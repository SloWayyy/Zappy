/*
** EPITECH PROJECT, 2023
** server
** File description:
** init.c
*/

#include <arpa/inet.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/signalfd.h>
#include <unistd.h>

#include "constants.h"
#include "types.h"
#include "util.h"

static bool init_signalfd(server_t *server)
{
    int sig_fd = 0;
    sigset_t mask;

    sigemptyset(&mask);
    sigaddset(&mask, SIGINT);
    sig_fd = signalfd(-1, &mask, 0);
    if (sig_fd == -1) {
        perror("signalfd failed");
        return false;
    }
    sigprocmask(SIG_BLOCK, &mask, NULL);
    server->signal_fd = sig_fd;
    return true;
}

static bool setup_socket(int socket_fd, int port)
{
    struct sockaddr *address = generate_address(port, NULL);
    int res = 0;

    if (address == NULL) {
        perror("malloc failed");
        return false;
    }
    res = bind(socket_fd, address, sizeof(*address));
    free(address);
    if (res == -1) {
        perror("bind failed");
        return false;
    }
    res = listen(socket_fd, MAX_CONNECTIONS);
    if (res == -1) {
        perror("listen failed");
        return false;
    }
    return true;
}

bool init_server(server_t *server)
{
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (socket_fd == -1) {
        perror("socket failed");
        return false;
    }
    if (!setup_socket(socket_fd, server->port)) {
        close(socket_fd);
        return false;
    }
    if (!init_signalfd(server)) {
        close(socket_fd);
        return false;
    }
    server->socket_fd = socket_fd;
    return true;
}
