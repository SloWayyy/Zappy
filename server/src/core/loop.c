/*
** EPITECH PROJECT, 2023
** server
** File description:
** loop.c
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/queue.h>
#include <sys/select.h>
#include <unistd.h>
#include <time.h>

#include "objects.h"
#include "server.h"
#include "types.h"

static void end_server(server_t *server)
{
    free_clients(server);
    free_teams(server);
    cancel_client_tasks(server, NULL);
    if (server->zappy->map != NULL) {
        free_map(server);
    }
    if (server->data->socket_fd != -1) {
        close(server->data->socket_fd);
    }
    if (server->data->signal_fd != -1) {
        close(server->data->signal_fd);
    }
    free(server->zappy->densities);
    free(server->zappy->empty);
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

static void init_values(server_t *server, tick_t *tick, team_list_t *teams)
{
    memset(server->data, 0, sizeof(data_t));
    memset(server->zappy, 0, sizeof(zappy_t));
    server->data->socket_fd = -1;
    server->data->signal_fd = -1;
    server->zappy->tick = tick;
    server->zappy->teams = teams;
    SLIST_INIT(server->clients);
    SLIST_INIT(server->zappy->teams);
    SLIST_INIT(server->tasks);
}

bool start_server(options_t *options)
{
    bool run = false;
    tick_t tick;
    data_t data;
    client_list_t clients;
    team_list_t teams;
    task_list_t tasks;
    zappy_t zappy;
    server_t server = { options, &data, &zappy, &clients, &tasks };

    srand(time(NULL) + (unsigned long)&server);
    init_values(&server, &tick, &teams);
    run = init_server(&server);
    if (run) {
        run = server_loop(&server);
    }
    end_server(&server);
    return run;
}
