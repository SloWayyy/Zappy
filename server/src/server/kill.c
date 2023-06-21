/*
** EPITECH PROJECT, 2023
** server
** File description:
** kill.c
*/

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <sys/queue.h>

#include "buffer.h"
#include "commands.h"
#include "constants.h"
#include "graphical.h"
#include "objects.h"
#include "resources.h"
#include "types.h"

static void kill_eggs(server_t *server, tile_t *source)
{
    egg_t *node = NULL;

    while (!SLIST_EMPTY(&source->eggs)) {
        node = SLIST_FIRST(&source->eggs);
        send_graphical_event(server, "%s %zu%s", \
            GRAPHICAL_PLAYER_EGG_DEATH, node->id, LINE_BREAK);
        SLIST_REMOVE(&source->eggs, node, egg, next_tile);
        SLIST_REMOVE(node->team->eggs, node, egg, next_team);
        free(node);
    }
}

static void kill_entities(server_t *server)
{
    for (int x = 0; x < server->options->width; x++) {
        for (int y = 0; y < server->options->height; y++) {
            memset(&server->zappy->map[y][x].resources, 0, \
                sizeof(size_t) * RESOURCES_TYPES_QUANTITY);
            kill_eggs(server, &server->zappy->map[y][x]);
        }
    }
    memset(server->zappy->current, 0, \
        sizeof(size_t) * RESOURCES_TYPES_QUANTITY);
    append_buffer(server->data->stdout_buffer, "%s%s", \
        SERVER_KILL_ENTITIES, LINE_BREAK);
    send_graphical_map_event(server);
}

static void kill_player(server_t *server, player_t *source)
{
    client_t *client = get_client_by_player_id(server, source->id);

    if (client == NULL) {
        return;
    }
    source->dead = true;
    append_buffer(server->data->stdout_buffer, SERVER_KILL_FORMAT, \
        source->id, LINE_BREAK);
    append_buffer(client->buffer_out, "%s%s", PLAYER_DEATH, LINE_BREAK);
}

static void kill_players(server_t *server, source_t *source)
{
    client_t *node = NULL;

    if (source->entities) {
        kill_entities(server);
    }
    if (source->all) {
        SLIST_FOREACH(node, server->clients, next) {
            if (node->type == PLAYER) {
                kill_player(server, node->player);
            }
        }
        return;
    }
    kill_player(server, source->player);
}

void kill_handler(server_t *server)
{
    char *args[2];
    source_t source = { NULL, false, false };

    for (int i = 0; i < 2; i++) {
        args[i] = strtok(NULL, " ");
    }
    if (args[0] == NULL || args[1] != NULL) {
        append_buffer(server->data->stdout_buffer, "%s%s", \
            SERVER_KILL_USAGE, LINE_BREAK);
        return;
    } else if (!get_source(server, args[0], &source)) {
        append_buffer(server->data->stdout_buffer, "%s %s%s", \
            SERVER_PLAYER_ERROR, args[0], LINE_BREAK);
        return;
    }
    kill_players(server, &source);
}
