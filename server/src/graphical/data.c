/*
** EPITECH PROJECT, 2023
** server
** File description:
** data.c
*/

#include <stddef.h>
#include <sys/queue.h>

#include "buffer.h"
#include "constants.h"
#include "graphical.h"
#include "types.h"

static void send_players(server_t *server, client_t *client)
{
    client_t *node = NULL;
    player_t *player = NULL;

    SLIST_FOREACH(node, server->clients, next) {
        if (node->type == PLAYER) {
            player = node->player;
            append_buffer(client->buffer_out, "%s %zu %zu %zu %zu %zu %s%s", \
                GRAPHICAL_PLAYER_JOIN, player->id, player->pos->x, \
                player->pos->y, player->direction + 1, player->level, \
                player->team->name, LINE_BREAK);
        }
    }
}

static void send_egg(client_t *client, egg_t *egg)
{
    if (egg->immortal) {
        append_buffer(client->buffer_out, "%s %s %zu %zu %zu%s", \
            GRAPHICAL_CUSTOM, GRAPHICAL_CUSTOM_EGG, egg->id, \
            egg->pos->x, egg->pos->y, LINE_BREAK);
    } else {
        append_buffer(client->buffer_out, "%s %zu %zu %zu %zu%s", \
            GRAPHICAL_PLAYER_EGG, egg->id, egg->player_id, \
            egg->pos->x, egg->pos->y, LINE_BREAK);
    }
}

static void send_eggs(server_t *server, client_t *client)
{
    egg_t *node = NULL;
    team_t *team = NULL;

    SLIST_FOREACH(team, server->zappy->teams, next) {
        SLIST_FOREACH(node, team->eggs, next_team) {
            send_egg(client, node);
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
    send_eggs(server, client);
}
