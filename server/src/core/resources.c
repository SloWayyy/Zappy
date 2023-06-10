/*
** EPITECH PROJECT, 2023
** server
** File description:
** resources.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "constants.h"
#include "server.h"
#include "types.h"

static double calculate_density(tile_t *tile, tile_t **empty)
{
    int index = 0;
    double density = 0.0;

    for (size_t i = 0; i < RESOURCES_TYPES_QUANTITY; i++) {
        density += tile->resources[i] * (1 - resources_density[i]);
    }
    if (density == 0.0) {
        while (empty[index] != NULL) {
            index++;
        }
        empty[index] = tile;
    }
    return density;
}

static double calculate_densities(server_t *server, double *densities, \
    tile_t **empty)
{
    double total = 0;
    double density = 0;

    for (int x = 0; x < server->options->width; x++) {
        for (int y = 0; y < server->options->height; y++) {
            density = calculate_density(&server->zappy->map[y][x], empty);
            densities[y * server->options->width + x] = density;
            total += density;
        }
    }
    return total;
}

void refill_callback(server_t *server, UNUSED client_t *client, \
    UNUSED void *arg)
{
    size_t area = server->options->width * server->options->height;
    double *densities = malloc(sizeof(double) * area);
    tile_t **empty = malloc(sizeof(tile_t *) * area);
    double total = 0.0;

    if (densities == NULL || empty == NULL) {
        perror("malloc failed");
        free(densities);
        free(empty);
        return;
    }
    memset(empty, 0, sizeof(tile_t *) * area);
    total = calculate_densities(server, densities, empty);
    refill_resources(server, total, densities, empty);
    memset(server->zappy->refill, 0, sizeof(size_t) * RESOURCES_TYPES_QUANTITY);
    free(densities);
    free(empty);
}
