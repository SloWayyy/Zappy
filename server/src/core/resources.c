/*
** EPITECH PROJECT, 2023
** server
** File description:
** resources.c
*/

#include <stdio.h>
#include <string.h>
#include <sys/param.h>
#include <sys/queue.h>

#include "constants.h"
#include "resources.h"
#include "server.h"
#include "types.h"

static double calculate_density(server_t *server, tile_t *tile)
{
    int index = 0;
    double density = 0.0;

    for (size_t i = 0; i < RESOURCES_TYPES_QUANTITY; i++) {
        density += tile->resources[i] * (1 - RESOURCES[i].density);
    }
    if (density == 0.0 && SLIST_EMPTY(&tile->players)) {
        while (server->zappy->empty[index] != NULL) {
            index++;
        }
        server->zappy->empty[index] = tile;
    }
    return density;
}

static double calculate_densities(server_t *server)
{
    double total = 0;
    double density = 0;

    for (int x = 0; x < server->options->width; x++) {
        for (int y = 0; y < server->options->height; y++) {
            density = calculate_density(server, &server->zappy->map[y][x]);
            server->zappy->densities[y * server->options->width + x] = density;
            total += density;
        }
    }
    return total;
}

void refill_callback(server_t *server, UNUSED client_t *client, \
    UNUSED void *arg)
{
    size_t area = server->options->width * server->options->height;
    double total = 0.0;

    memset(server->zappy->densities, 0, sizeof(double) * area);
    memset(server->zappy->empty, 0, sizeof(tile_t *) * area);
    total = calculate_densities(server);
    refill_resources(server, total);
    for (size_t i = 0; i < RESOURCES_TYPES_QUANTITY; i++) {
        server->zappy->current[i] = MAX(server->zappy->current[i], \
            server->zappy->total[i]);
    }
}
