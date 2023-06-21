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
    player_t *back = NULL;
    size_t size = 0;
    size_t index = 0;

    SLIST_FOREACH(node, server->clients, next) {
        if (node->type == PLAYER) {
            back = node->player;
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
    return back;
}

static bool handle_modifiers(server_t *server, char *target, source_t *source)
{
    if (strcmp(target, SERVER_MODIFIER_ALL_PLAYERS) == 0) {
        source->all = true;
        return true;
    }
    if (strcmp(target, SERVER_MODIFIER_ALL_ENTITIES) == 0) {
        source->all = true;
        source->entities = true;
        return true;
    }
    if (strcmp(target, SERVER_MODIFIER_RANDOM) == 0) {
        source->player = get_random_player(server);
        return source->player != NULL;
    }
    return false;
}

bool get_source(server_t *server, char *target, source_t *source)
{
    int id = 0;
    client_t *client = NULL;

    if (handle_modifiers(server, target, source)) {
        return true;
    } else if (!check_number(target, &id)) {
        return false;
    }
    client = get_client_by_player_id(server, id);
    if (client != NULL) {
        source->player = client->player;
        return true;
    }
    return false;
}
