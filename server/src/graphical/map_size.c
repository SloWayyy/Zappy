/*
** EPITECH PROJECT, 2023
** server
** File description:
** map_size.c
*/

#include <string.h>

#include "buffer.h"
#include "constants.h"
#include "graphical.h"
#include "types.h"

void send_map_size(server_t *server, client_t *client)
{
    append_buffer(client->buffer_out, "%s %d %d%s", \
        GRAPHICAL_MAP_SIZE, server->options->width, server->options->height, \
        LINE_BREAK);
}

void msz_handler(server_t *server, client_t *client)
{
    if (strtok(NULL, " ") != NULL) {
        append_buffer(client->buffer_out, "%s%s", GRAPHICAL_COMMAND_PARAMETER, \
            LINE_BREAK);
        return;
    }
    send_map_size(server, client);
}
