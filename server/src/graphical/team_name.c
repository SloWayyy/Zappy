/*
** EPITECH PROJECT, 2023
** server
** File description:
** team_name.c
*/

#include <string.h>

#include "constants.h"
#include "graphical.h"
#include "types.h"
#include "util.h"

void tna_handler(server_t *server, client_t *client)
{
    if (strtok(NULL, " ") != NULL) {
        append_buffer(client->buffer_out, "%s%s", GRAPHICAL_COMMAND_PARAMETER, \
            LINE_BREAK);
        return;
    }
    for (size_t i = 0; server->options->names[i] != NULL; i++) {
        append_buffer(client->buffer_out, "%s %s%s", GRAPHICAL_TEAMS_NAMES, \
            server->options->names[i], LINE_BREAK);
    }
}
