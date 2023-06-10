/*
** EPITECH PROJECT, 2023
** server
** File description:
** map.c
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/param.h>
#include <sys/queue.h>

#include "constants.h"
#include "server.h"
#include "types.h"

static bool populate_map(server_t *server)
{
    double density = 0.0;
    task_t *task = register_task(server, NULL, &refill_callback);

    if (task == NULL) {
        return false;
    }
    for (size_t i = 0; i < RESOURCES_TYPES_QUANTITY; i++) {
        density = resources_density[i] * \
            server->options->width * server->options->height;
        server->zappy->total[i] = MAX(1, density);
        server->zappy->refill[i] = server->zappy->total[i];
    }
    refill_callback(server, NULL, NULL);
    schedule_task(task, server, REFILL_DELAY, -1);
    return true;
}

static void init_tiles(server_t *server)
{
    for (int i = 0; i < server->options->height; i++) {
        for (int j = 0; j < server->options->width; j++) {
            server->zappy->map[i][j].x = j;
            server->zappy->map[i][j].y = i;
            SLIST_INIT(&server->zappy->map[i][j].players);
            SLIST_INIT(&server->zappy->map[i][j].eggs);
        }
    }
}

void free_map(server_t *server)
{
    for (int i = 0; i < server->options->height; i++) {
        free(server->zappy->map[i]);
    }
    free(server->zappy->map);
}

bool init_map(server_t *server)
{
    size_t array_size = sizeof(tile_t) * (server->options->height);

    server->zappy->map = malloc(sizeof(tile_t *) * (server->options->height));
    if (server->zappy->map == NULL) {
        perror("malloc failed");
        return false;
    }
    memset(server->zappy->map, 0, sizeof(tile_t *) * (server->options->height));
    for (int i = 0; i < server->options->height; i++) {
        server->zappy->map[i] = malloc(array_size);
        if (server->zappy->map[i] == NULL) {
            perror("malloc failed");
            return false;
        }
        memset(server->zappy->map[i], 0, array_size);
    }
    init_tiles(server);
    return populate_map(server);
}
