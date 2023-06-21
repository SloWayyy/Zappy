/*
** EPITECH PROJECT, 2023
** server
** File description:
** events.c
*/

#include <stdarg.h>
#include <stddef.h>
#include <sys/queue.h>

#include "buffer.h"
#include "constants.h"
#include "graphical.h"
#include "types.h"

void send_graphical_event(server_t *server, const char *format, ...)
{
    va_list list;
    va_list copy;
    client_t *node = NULL;

    va_start(list, format);
    SLIST_FOREACH(node, server->clients, next) {
        if (node->type == GRAPHIC) {
            va_copy(copy, list);
            vappend_buffer(node->buffer_out, format, copy);
            va_end(copy);
        }
    }
    va_end(list);
}

void send_graphical_position_event(server_t *server, player_t *player)
{
    send_graphical_event(server, "%s %zu %d %d %zu%s", \
        GRAPHICAL_PLAYER_POSITION, player->id, player->pos->x, \
        player->pos->y, player->direction + 1, LINE_BREAK);
}

void send_graphical_join_event(server_t *server, client_t *client)
{
    send_graphical_event(server, "%s %zu %zu %zu %zu %zu %s%s", \
        GRAPHICAL_PLAYER_JOIN, client->player->id, client->player->pos->x, \
        client->player->pos->y, client->player->direction + 1, \
        client->player->level, client->player->team->name, LINE_BREAK);
}

void send_graphical_tile_event(server_t *server, tile_t *tile)
{
    client_t *node = NULL;

    SLIST_FOREACH(node, server->clients, next) {
        if (node->type == GRAPHIC) {
            send_tile(server, node, tile->x, tile->y);
        }
    }
}
