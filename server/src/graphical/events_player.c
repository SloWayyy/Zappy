/*
** EPITECH PROJECT, 2023
** server
** File description:
** player_events.c
*/

#include <stddef.h>

#include "constants.h"
#include "graphical.h"
#include "types.h"
#include "resources.h"

void send_graphical_join_event(server_t *server, player_t *player)
{
    send_graphical_event(server, "%s %zu %zu %zu %zu %zu %s%s", \
        GRAPHICAL_PLAYER_JOIN, player->id, player->pos->x, player->pos->y, \
        player->direction + 1, player->level, player->team->name, LINE_BREAK);
}

void send_graphical_inventory_event(server_t *server, player_t *player)
{
    send_graphical_event(server, "%s %zu %zu %zu", \
        GRAPHICAL_PLAYER_INVENTORY, player->id, \
        player->pos->x, player->pos->y);
    for (size_t i = 0; i < RESOURCES_TYPES_QUANTITY; i++) {
        send_graphical_event(server, " %zu", player->inventory[i]);
    }
    send_graphical_event(server, "%s", LINE_BREAK);
}

void send_graphical_position_event(server_t *server, player_t *player)
{
    send_graphical_event(server, "%s %zu %d %d %zu%s", \
        GRAPHICAL_PLAYER_POSITION, player->id, player->pos->x, \
        player->pos->y, player->direction + 1, LINE_BREAK);
}
