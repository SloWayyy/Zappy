/*
** EPITECH PROJECT, 2023
** server
** File description:
** eject.c
*/

#include <stdbool.h>
#include <stdlib.h>
#include <sys/queue.h>

#include "buffer.h"
#include "constants.h"
#include "graphical.h"
#include "objects.h"
#include "player.h"
#include "tasks.h"
#include "types.h"
#include "util.h"

static void eject_player(server_t *server, client_t *client, player_t *target, \
    tile_t *tile)
{
    client_t *node = get_client_by_player_id(server, target->id);

    if (node == NULL) {
        return;
    }
    SLIST_REMOVE(&target->pos->players, target, player, next_tile);
    SLIST_INSERT_HEAD(&tile->players, target, next_tile);
    target->pos = tile;
    append_buffer(node->buffer_out, "%s %zu%s", \
        PLAYER_EJECTION, client->player->direction + 1, LINE_BREAK);
    send_graphical_position_event(server, node->player);
}

static bool eject_players(server_t *server, client_t *client)
{
    bool eject = false;
    player_t *node = NULL;
    vector_t vector = get_direction(client->player->direction);
    int pos_x = (int) client->player->pos->x + vector.x;
    int pos_y = (int) client->player->pos->y + vector.y;

    pos_x = (pos_x + server->options->width) % server->options->width;
    pos_y = (pos_y + server->options->height) % server->options->height;
    SLIST_FOREACH(node, &client->player->pos->players, next_tile) {
        if (node == client->player) {
            continue;
        }
        if (!eject) {
            send_graphical_event(server, "%s %zu%s", \
                GRAPHICAL_PLAYER_EJECT, client->player->id, LINE_BREAK);
            eject = true;
        }
        eject_player(server, client, node, &server->zappy->map[pos_y][pos_x]);
    }
    return eject;
}

static void eject_eggs(server_t *server, client_t *client)
{
    egg_t *node = NULL;
    egg_t *tmp = NULL;

    SLIST_FOREACH(node, &client->player->pos->eggs, next_tile) {
        tmp = SLIST_NEXT(node, next_tile);
        if (!node->immortal) {
            SLIST_REMOVE(node->team->eggs, node, egg, next_team);
            SLIST_REMOVE(&client->player->pos->eggs, node, egg, next_tile);
            send_graphical_event(server, "%s %zu%s", \
                GRAPHICAL_PLAYER_EGG_DEATH, node->id, LINE_BREAK);
            free(node);
        }
        node = tmp;
    }
}

static void eject_callback(server_t *server, client_t *client, UNUSED void *arg)
{
    bool eject = false;

    eject = eject_players(server, client);
    eject_eggs(server, client);
    append_buffer(client->buffer_out, "%s%s", \
        (eject ? PLAYER_OK : PLAYER_KO), LINE_BREAK);
    flush_command(server, client);
}

bool eject_handler(server_t *server, client_t *client, UNUSED char *line)
{
    setup_task(client->player->action_task, &eject_callback, NULL);
    schedule_task(client->player->action_task, server, EJECT_DELAY, 1);
    return true;
}
