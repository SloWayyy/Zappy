/*
** EPITECH PROJECT, 2023
** server
** File description:
** teleportation.c
*/

#include <string.h>
#include <sys/queue.h>

#include "buffer.h"
#include "commands.h"
#include "constants.h"
#include "graphical.h"
#include "types.h"
#include "resources.h"

static void teleport_eggs(server_t *server, tile_t *source, tile_t *dest)
{
    egg_t *node = NULL;

    if (source == dest)
        return;
    while (!SLIST_EMPTY(&source->eggs)) {
        node = SLIST_FIRST(&source->eggs);
        SLIST_REMOVE(&source->eggs, node, egg, next_tile);
        node->pos = dest;
        SLIST_INSERT_HEAD(&dest->eggs, node, next_tile);
        send_graphical_event(server, "%s %zu%s", \
            GRAPHICAL_PLAYER_EGG_DEATH, node->id, LINE_BREAK);
        send_graphical_egg_event(server, node);
    }
}

static void teleport_entities(server_t *server, tile_t *dest)
{
    for (int x = 0; x < server->options->width; x++) {
        for (int y = 0; y < server->options->height; y++) {
            memset(&server->zappy->map[y][x].resources, 0, \
                sizeof(size_t) * RESOURCES_TYPES_QUANTITY);
            teleport_eggs(server, &server->zappy->map[y][x], dest);
        }
    }
    for (size_t i = 0; i < RESOURCES_TYPES_QUANTITY; i++) {
        dest->resources[i] = server->zappy->current[i];
    }
    send_graphical_map_event(server);
}

static void teleport_player(server_t *server, player_t *source, tile_t *dest, \
    direction_type_t direction)
{
    SLIST_REMOVE(&source->pos->players, source, player, next_tile);
    source->pos = dest;
    SLIST_INSERT_HEAD(&dest->players, source, next_tile);
    source->direction = direction;
    append_buffer(server->data->stdout_buffer, SERVER_TP_FORMAT, \
        source->id, dest->x, dest->y, LINE_BREAK);
    send_graphical_position_event(server, source);
}

void teleport_players(server_t *server, source_t *source, tile_t *dest, \
    direction_type_t *ptr)
{
    client_t *node = NULL;
    direction_type_t direction = NORTH;

    if (source->entities) {
        teleport_entities(server, dest);
        append_buffer(server->data->stdout_buffer,\
            SERVER_TP_ENTITIES, dest->x, dest->y, LINE_BREAK);
    }
    if (source->all) {
        SLIST_FOREACH(node, server->clients, next) {
            if (node->type == PLAYER) {
                direction = ptr == NULL ? node->player->direction : *ptr;
                teleport_player(server, node->player, dest, direction);
            }
        }
        return;
    }
    if (ptr == NULL)
        direction = source->player->direction;
    teleport_player(server, source->player, dest, direction);
}
