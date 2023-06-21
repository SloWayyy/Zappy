/*
** EPITECH PROJECT, 2023
** server
** File description:
** events.c
*/

#include <stddef.h>
#include <sys/queue.h>

#include "graphical.h"
#include "types.h"

void send_graphical_map_event(server_t *server)
{
    client_t *node = NULL;

    SLIST_FOREACH(node, server->clients, next) {
        if (node->type == GRAPHIC) {
            send_map(server, node);
        }
    }
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

void send_graphical_egg_event(server_t *server, egg_t *egg)
{
    client_t *node = NULL;

    SLIST_FOREACH(node, server->clients, next) {
        if (node->type == GRAPHIC) {
            send_egg(node, egg);
        }
    }
}
