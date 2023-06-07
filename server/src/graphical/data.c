/*
** EPITECH PROJECT, 2023
** server
** File description:
** data.c
*/

#include <stddef.h>
#include <sys/queue.h>

#include "constants.h"
#include "graphical.h"
#include "types.h"
#include "util.h"

static void send_players(server_t *server, client_t *client)
{
    client_t *node = NULL;
    player_t *player = NULL;

    SLIST_FOREACH(node, server->clients, next) {
        if (node->type == PLAYER) {
            player = node->player;
            append_buffer(client->buffer_out, "%s %zu %zu %zu %zu %zu %s%s", \
                GRAPHICAL_PLAYER_JOIN, player->id, player->pos->x, \
                player->pos->y, player->direction, player->level, \
                player->team->name, LINE_BREAK);
        }
    }
}

void send_new_graphical(server_t *server, client_t *client)
{
    send_map_size(server, client);
    send_time(server, client);
    send_map(server, client);
    send_team_names(server, client);
    send_players(server, client);
}
