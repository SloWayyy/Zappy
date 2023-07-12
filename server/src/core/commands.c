/*
** EPITECH PROJECT, 2023
** server
** File description:
** commands.c
*/

#include <string.h>
#include <sys/queue.h>

#include "buffer.h"
#include "constants.h"
#include "graphical.h"
#include "player.h"
#include "types.h"

static void handle_unknown(server_t *server, client_t *client, char *line)
{
    if (strcmp(line, GRAPHICAL_IDENTIFIER) == 0) {
        client->type = GRAPHIC;
        send_new_graphical(server, client);
    } else if (try_join_team(server, client, line)) {
        client->type = PLAYER;
        append_buffer(client->buffer_out, "%d%s%d %d%s", \
            client->player->team->slots, LINE_BREAK, \
            server->options->width, server->options->height, LINE_BREAK);
    } else {
        append_buffer(client->buffer_out, "%s%s", PLAYER_UNKNOWN, \
            LINE_BREAK);
    }
}

static void handle_empty(server_t *server, client_t *client)
{
    team_t *team = NULL;

    if (client->type != UNKNOWN) {
        return;
    }
    SLIST_FOREACH(team, server->zappy->teams, next) {
        if (strcmp(team->name, "") == 0) {
            handle_unknown(server, client, "");
            return;
        }
    }
}

void handle_client_input(server_t *server, client_t *client, char *line)
{
    if (strlen(line) == 0) {
        handle_empty(server, client);
        return;
    }
    if (client->type == PLAYER) {
        register_command(server, client, line);
    } else if (client->type == GRAPHIC) {
        handle_graphical_command(server, client, line);
    } else {
        handle_unknown(server, client, line);
    }
}
