/*
** EPITECH PROJECT, 2023
** server
** File description:
** team_name.c
*/

#include <string.h>

#include "buffer.h"
#include "constants.h"
#include "graphical.h"
#include "types.h"

void send_team_names(server_t *server, client_t *client)
{
    for (size_t i = 0; server->options->names[i] != NULL; i++) {
        append_buffer(client->buffer_out, "%s %s%s", GRAPHICAL_TEAMS_NAMES, \
            server->options->names[i], LINE_BREAK);
    }
}

void tna_handler(server_t *server, client_t *client)
{
    if (strtok(NULL, " ") != NULL) {
        append_buffer(client->buffer_out, "%s%s", GRAPHICAL_COMMAND_PARAMETER, \
            LINE_BREAK);
        return;
    }
    send_team_names(server, client);
}
