/*
** EPITECH PROJECT, 2023
** server
** File description:
** modifiers.c
*/

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <sys/queue.h>

#include "commands.h"
#include "objects.h"
#include "server.h"
#include "types.h"

static player_t *get_random_player(server_t *server)
{
    client_t *node = NULL;
    size_t size = 0;
    size_t index = 0;

    SLIST_FOREACH(node, server->clients, next) {
        if (node->type == PLAYER) {
            size++;
        }
    }
    index = rand() % size;
    SLIST_FOREACH(node, server->clients, next) {
        if (node->type == PLAYER && index == 0) {
            return node->player;
        }
        index -= node->type == PLAYER;
    }
    return NULL;
}

bool get_source(server_t *server, char *target, player_t **ptr)
{
    int id = 0;
    client_t *client = NULL;

    if (strcmp(target, SERVER_MODIFIER_ALL) == 0) {
        *ptr = NULL;
        return true;
    } else if (strcmp(target, SERVER_MODIFIER_RANDOM) == 0) {
        *ptr = get_random_player(server);
        return *ptr != NULL;
    }
    if (!check_number(target, &id)) {
        return false;
    }
    client = get_client_by_player_id(server, id);
    if (client != NULL) {
        *ptr = client->player;
        return true;
    }
    return false;
}
