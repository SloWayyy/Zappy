/*
** EPITECH PROJECT, 2023
** server
** File description:
** team_name.c
*/

#include <stddef.h>

#include "constants.h"
#include "graphical.h"
#include "types.h"
#include "util.h"

void tna_handler(server_t *server, client_t *client)
{
    if (strtok(NULL, " ") != NULL) {
        append_buffer(client->buffer, "%s%s", GRAPHICAL_COMMAND_PARAMETER, \
            LINE_BREAK);
        return;
    }
    for (size_t i = 0; server->options->names[i] != NULL; i++) {
        append_buffer(client->buffer, "%s %s%s", GRAPHICAL_TEAM_NAME, \
            server->options->names[i], LINE_BREAK);
    }
}
