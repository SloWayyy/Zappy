/*
** EPITECH PROJECT, 2023
** server
** File description:
** map_answers.c
*/

#include <stdbool.h>
#include <string.h>

#include "buffer.h"
#include "constants.h"
#include "graphical.h"
#include "resources.h"
#include "server.h"
#include "types.h"

static bool check_map_coord(server_t *server, int x, int y, client_t *client)
{
    if (x < 0 || x >= server->options->width || y < 0
        || y >= server->options->height) {
        append_buffer(client->buffer_out, "%s%s", \
            GRAPHICAL_COMMAND_PARAMETER, LINE_BREAK);
        return false;
        }
    return true;
}

void send_tile(server_t *server, client_t *client, int x, int y)
{
    append_buffer(client->buffer_out, "%s %zu %zu", \
        GRAPHICAL_TILE_CONTENT, x, y);
    for (size_t i = 0; i < RESOURCES_TYPES_QUANTITY; i++) {
        append_buffer(client->buffer_out, " %zu", \
            server->zappy->map[y][x].resources[i]);
    }
    append_buffer(client->buffer_out, "%s", LINE_BREAK);
}

void send_map(server_t *server, client_t *client)
{
    for (int y = 0; y < server->options->height; y++) {
        for (int x = 0; x < server->options->width; x++) {
            send_tile(server, client, x, y);
        }
    }
}

void bct_handler(server_t *server, client_t *client)
{
    char *input_x = strtok(NULL, " ");
    char *input_y = strtok(NULL, " ");
    int x = 0;
    int y = 0;

    if (input_x == NULL || input_y == NULL || strtok(NULL, " ") != NULL ||
        !check_number(input_x, &x) || !check_number(input_x, &y)) {
        append_buffer(client->buffer_out, "%s%s", GRAPHICAL_COMMAND_PARAMETER, \
            LINE_BREAK);
        return;
    }
    if (!check_map_coord(server, x, y, client)) {
        return;
    }
    send_tile(server, client, x, y);
}

void mct_handler(server_t *server, client_t *client)
{
    if (strtok(NULL, " ") != NULL) {
        append_buffer(client->buffer_out, "%s%s", GRAPHICAL_COMMAND_PARAMETER, \
            LINE_BREAK);
        return;
    }
    send_map(server, client);
}
