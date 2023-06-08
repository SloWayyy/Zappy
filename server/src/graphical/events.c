/*
** EPITECH PROJECT, 2023
** server
** File description:
** events.c
*/

#include <stdarg.h>
#include <stddef.h>
#include <sys/queue.h>

#include "constants.h"
#include "graphical.h"
#include "types.h"
#include "util.h"

void send_graphical_event(server_t *server, const char *format, ...)
{
    va_list list;
    va_list copy;
    client_t *node = NULL;

    va_start(list, format);
    SLIST_FOREACH(node, server->clients, next) {
        va_copy(copy, list);
        if (node->type == GRAPHIC) {
            vappend_buffer(node->buffer_out, format, copy);
        }
        va_end(copy);
    }
    va_end(list);
}

void send_graphical_position_event(server_t *server, client_t *client)
{
    send_graphical_event(server, "%s %zu %d %d %zu%s", \
        GRAPHICAL_PLAYER_POSITION, client->player->id, client->player->pos->x, \
        client->player->pos->y, client->player->direction, LINE_BREAK);
}
