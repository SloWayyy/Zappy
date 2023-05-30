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
        close_connection(current);
        free_connection(current);
    }
    close(server->data->socket_fd);
}

static bool server_loop(server_t *server)
{
    bool exit = false;
    int max_fd = 0;
    int res = 0;

    start_game(server);
    while (!exit) {
        refresh_timeout(server);
        max_fd = refresh_fdsets(server);
        res = select(max_fd + 1, &server->data->reads, &server->data->writes, \
            NULL, &server->data->timeout);
        if (res == -1) {
            perror("select failed");
            return false;
        }
        exit = res > 0 ? handle_fdsets(server) : tick(server);
    }
    return true;
}

bool start_server(options_t *options)
{
    tick_t tick;
    zappy_t zappy = { &tick };
    data_t data;
    struct client_list clients;
    server_t server = {  options, &data, &zappy, &clients };

    SLIST_INIT(&clients);
    if (!init_server(&server)) {
        return false;
    }
    server_loop(&server);
    end_server(&server);
    return true;
}
