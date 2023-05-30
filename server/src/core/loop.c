/*
** EPITECH PROJECT, 2023
** server
** File description:
** loop.c
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/queue.h>
#include <sys/select.h>
#include <unistd.h>

#include "server.h"
#include "types.h"

static void end_server(server_t *server)
{
    client_t *current = NULL;

    while (!SLIST_EMPTY(server->clients)) {
        current = SLIST_FIRST(server->clients);
        SLIST_REMOVE_HEAD(server->clients, next);
        close(current->fd);
        free(current);
    }
    close(server->socket_fd);
}

static bool server_loop(server_t *server)
{
    bool exit = false;
    int max_fd = 0;
    int res = 0;
    fd_set set;

    while (!exit) {
        max_fd = refresh_fdsets(server, &set);
        res = select(max_fd + 1, &set, NULL, NULL, NULL);
        if (res == -1) {
            perror("select failed");
            return false;
        }
        if (res > 0) {
            exit = handle_fdsets(server, &set);
        } else {
            // TODO: Global tick
        }
    }
    return true;
}

bool start_server(options_t *options)
{
    struct client_list clients;
    server_t server = { options->port, 0, 0, &clients };

    SLIST_INIT(&clients);
    if (!init_server(&server)) {
        return false;
    }
    server_loop(&server);
    end_server(&server);
    return true;
}
