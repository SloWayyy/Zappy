/*
** EPITECH PROJECT, 2023
** server
** File description:
** map_answers.c
*/

#include "constants.h"
#include "graphical.h"
#include "util.h"
#include "types.h"

void msz_handler(server_t *server, client_t *client)
{
    if (strtok(NULL, " ") != NULL) {
        append_buffer(client->buffer, "%s%s", GRAPHICAL_COMMAND_PARAMETER, \
            LINE_BREAK);
        return;
    }
    append_buffer(client->buffer, "%s %d %d%s", GRAPHICAL_MAP_SIZE, \
        server->options->width, server->options->height, LINE_BREAK);
}
