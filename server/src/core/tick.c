/*
** EPITECH PROJECT, 2023
** server
** File description:
** map.c
*/

#include <stdbool.h>
#include <stdio.h>
#include <sys/time.h>

#include "types.h"
#include "util.h"

void start_game(server_t *server)
{
    gettimeofday(&server->zappy->tick->game_start, NULL);
    gettimeofday(&server->zappy->tick->last_tick, NULL);
}

void refresh_timeout(server_t *server)
{
    struct timeval now;
    struct timeval elapsed;

    gettimeofday(&now, NULL);
    get_elapsed_time(&server->zappy->tick->last_tick, &now, &elapsed);
    get_elapsed_time(&elapsed, &server->zappy->tick->tick_delay, \
        &server->data->timeout);
}

bool tick(server_t *server)
{
    server->zappy->tick->tick_nb += 1;
    gettimeofday(&server->zappy->tick->last_tick, NULL);
    printf("Tick %zu\n", server->zappy->tick->tick_nb);
    return false;
}
