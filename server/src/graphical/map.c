/*
** EPITECH PROJECT, 2023
** server
** File description:
** map_answers.c
*/

#include <string.h>

#include "constants.h"
#include "graphical.h"
#include "server.h"
#include "types.h"
#include "util.h"

void msz_handler(server_t *server, client_t *client)
{
    append_buffer(client->buffer, "%s %d %d%s", GRAPHICAL_MAP_SIZE, \
        server->options->width, server->options->height, LINE_BREAK);
}

static bool check_map_coord(server_t *server, const int x, const int y,
client_t *client)
{
    if (x < 0 || x >= server->options->width || y < 0
        || y >= server->options->height) {
        append_buffer(client->buffer, "%s%s", GRAPHICAL_COMMAND_PARAMETER, \
            LINE_BREAK);
        return false;
        }
    return true;
}

static void send_tile(server_t *server, client_t *client,
const int x, const int y)
{
    append_buffer(client->buffer, "%zu %zu %zu %zu %zu %zu", \
        server->zappy->map[y][x].resources[0], \
        server->zappy->map[y][x].resources[1], \
        server->zappy->map[y][x].resources[2], \
        server->zappy->map[y][x].resources[3], \
        server->zappy->map[y][x].resources[4], \
        server->zappy->map[y][x].resources[5]);
}

void bct_handler(server_t *server, client_t *client)
{
    char *intput_x = strtok(NULL, " ");
    char *intput_y = strtok(NULL, " ");
    int x = 0;
    int y = 0;

    if (intput_x == NULL || intput_y == NULL || strtok(NULL, " ") != NULL ||
        !check_number(intput_x, &x) || !check_number(intput_y, &y)) {
        append_buffer(client->buffer, "%s\n", GRAPHICAL_COMMAND_PARAMETER);
        return;
    }
    if (!check_map_coord(server, x, y, client))
        return;
    append_buffer(client->buffer, "%s %zu %zu ", \
        GRAPHICAL_TILE_CONTENT, x, y);
    send_tile(server, client, x, y);
    append_buffer(client->buffer, "%s", LINE_BREAK);
}

void mct_handler(server_t *server, client_t *client)
{
    if (strtok(NULL, " ") != NULL) {
        append_buffer(client->buffer, "%s%s", GRAPHICAL_COMMAND_PARAMETER, \
            LINE_BREAK);
        return;
    }
    for (int y = 0; y < server->options->height; y++) {
        for (int x = 0; x < server->options->width; x++) {
            append_buffer(client->buffer, "%s %zu %zu ", \
                GRAPHICAL_ALL_TILE_CONTENT, x, y);
            send_tile(server, client, x, y);
            append_buffer(client->buffer, "%s", LINE_BREAK);
        }
    }
}
