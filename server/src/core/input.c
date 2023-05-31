/*
** EPITECH PROJECT, 2023
** server
** File description:
** input.c
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graphical.h"
#include "player.h"
#include "types.h"
#include "util.h"

static void handle_unknown(server_t *server, client_t *client, char *line)
{
    if (strcmp(line, GRAPHICAL_IDENTIFIER) == 0) {
        client->type = GRAPHIC;
        // TODO: Send graphical data
    } else if (try_join_team(server, client, line)) {
        // TODO: Send player data
    } else {
        append_buffer(client->buffer, PLAYER_UNKNOWN_COMMAND);
    }
}

static void handle_client_input(server_t *server, client_t *client, char *line)
{
    if (client->type == PLAYER) {
        handle_player_command(server, client, line);
    } else if (client->type == GRAPHIC) {
        handle_graphical_command(server, client, line);
    } else {
        handle_unknown(server, client, line);
    }
}

bool handle_input(server_t *server, client_t *client)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t res = getline(&line, &len, client->stream);

    if (res == -1) {
        free(line);
        return false;
    }
    if (res == 1) {
        return true;
    }
    line[res - 1] = '\0';
    handle_client_input(server, client, line);
    free(line);
    return true;
}
