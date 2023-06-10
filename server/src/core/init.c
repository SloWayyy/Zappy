/*
** EPITECH PROJECT, 2023
** server
** File description:
** init.c
*/

#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/queue.h>
#include <sys/signalfd.h>
#include <sys/socket.h>

#include "constants.h"
#include "objects.h"
#include "server.h"
#include "types.h"
#include "util.h"

static bool init_zappy(server_t *server)
{
    team_t *team = NULL;

    init_tick(server, server->options->freq);
    server->zappy->tick->tick_nb = 0;
    if (!init_map(server)) {
        return false;
    }
    for (int i = 0; server->options->names[i] != NULL; i++) {
        team = new_team(server->options->names[i], server->options->clients);
        if (team == NULL) {
            return false;
        }
        SLIST_INSERT_HEAD(server->zappy->teams, team, next);
    }
    return true;
}

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
    server->data->signal_fd = sig_fd;
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
    int fd = socket(AF_INET, SOCK_STREAM, 0);

    if (fd == -1) {
        perror("socket failed");
        return false;
    }

    server->data->socket_fd = fd;
    if (!setup_socket(fd, server->options->port) || !init_signalfd(server)) {
        return false;
    }
    if (!init_zappy(server)) {
        return false;
    }
    return true;
}
