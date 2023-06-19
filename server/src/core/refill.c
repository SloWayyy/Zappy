/*
** EPITECH PROJECT, 2023
** server
** File description:
** refill.c
*/

#include <stdlib.h>

#include "constants.h"
#include "resources.h"
#include "types.h"

static tile_t *choose_empty(tile_t **empty, size_t area)
{
    size_t size = 0;
    size_t index = 0;
    tile_t *tile = NULL;

    while (size < area && empty[size] != NULL) {
        size++;
    }
    index = rand() % size;
    tile = empty[index];
    empty[index] = empty[size - 1];
    empty[size - 1] = NULL;
    return tile;
}

static tile_t *calculate_ascending(server_t *server, size_t area, int nb)
{
    int i = 0;

    for (size_t index = 0; index < area; index++) {
        i += server->zappy->densities[index] * REFILL_COEFFICIENT;
        if (i >= nb) {
            return &server->zappy->map[index / server->options->width] \
                [index % server->options->width];
        }
    }
    return &server->zappy->map[0][0];
}

static tile_t *calculate_descending(server_t *server, size_t area, int nb)
{
    for (size_t index = 0; index < area; index++) {
        nb -= server->zappy->densities[index] * REFILL_COEFFICIENT;
        if (nb <= 0) {
            return &server->zappy->map[index / server->options->width] \
                [index % server->options->width];
        }
    }
    return &server->zappy->map[0][0];
}

static tile_t *choose_tile(server_t *server, double total)
{
    int nb = 0;
    int mode = 0;
    int total_rand = 0;
    size_t area = server->options->width * server->options->height;

    if (server->zappy->empty[0] != NULL) {
        return choose_empty(server->zappy->empty, area);
    }
    total_rand = total * REFILL_COEFFICIENT;
    nb = rand() % total_rand;
    mode = rand() % 2;
    if (mode == 0) {
        return calculate_descending(server, area, nb);
    } else {
        return calculate_ascending(server, area, nb);
    }
}

void refill_resources(server_t *server, double total)
{
    size_t coords = 0;
    size_t amount = 0;
    tile_t *tile = NULL;

    for (size_t index = 0; index < RESOURCES_TYPES_QUANTITY; index++) {
        amount = server->zappy->total[index] - server->zappy->current[index];
        if (server->zappy->total[index] <= server->zappy->current[index]) {
            continue;
        }
        for (size_t nb = 0; nb < amount; nb++) {
            tile = choose_tile(server, total);
            tile->resources[index] += 1;
            coords = tile->y * server->options->width + tile->x;
            server->zappy->densities[coords] += 1 - RESOURCES[index].density;
            total += 1 - RESOURCES[index].density;
        }
    }
}
