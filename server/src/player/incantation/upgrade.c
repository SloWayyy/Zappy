/*
** EPITECH PROJECT, 2023
** server
** File description:
** upgrade.c
*/

#include <stdbool.h>
#include <stddef.h>
#include <sys/queue.h>

#include "buffer.h"
#include "constants.h"
#include "graphical.h"
#include "objects.h"
#include "player.h"
#include "resources.h"
#include "types.h"

static void end_incantation_error(server_t *server, incantation_t *incantation)
{
    player_t *node = NULL;
    client_t *target = NULL;

    SLIST_FOREACH(node, &incantation->players, next_incantation) {
        target = get_client_by_player_id(server, node->id);
        if (target != NULL) {
            append_buffer(target->buffer_out, "%s%s", PLAYER_KO, LINE_BREAK);
            flush_command(server, target);
        }
    }
}

static void notify_players(server_t *server, incantation_t *incantation)
{
    player_t *node = NULL;
    client_t *target = NULL;

    SLIST_FOREACH(node, &incantation->players, next_incantation) {
        target = get_client_by_player_id(server, node->id);
        node->level += 1;
        debug(server, "Player %zu leveled up to %zu", node->id, node->level);
        send_graphical_event(server, "%s %zu %zu%s", \
            GRAPHICAL_PLAYER_LEVEL, node->id, node->level, LINE_BREAK);
        if (target != NULL) {
            append_buffer(target->buffer_out, "%s %zu%s", \
                PLAYER_ELEVATION_END, node->level, LINE_BREAK);
            flush_command(server, target);
        }
    }
}

static void end_incantation_success(server_t *server, \
    incantation_t *incantation, tile_t *tile)
{
    for (size_t i = 0; i < RESOURCES_TYPES_QUANTITY; i++) {
        tile->resources[i] -= incantation->requirements->resources[i];
        server->zappy->current[i] -= incantation->requirements->resources[i];
    }
    send_graphical_tile_event(server, tile);
    notify_players(server, incantation);
    check_victory(server, incantation);
}

void incantation_callback(server_t *server, UNUSED client_t *client, void *arg)
{
    incantation_t *incantation = (incantation_t *) arg;
    bool done = false;
    player_t *node = NULL;

    debug(server, "Starting post incantation verification");
    done = meet_requirements(server, incantation);
    if (SLIST_EMPTY(&incantation->players)) {
        return;
    }
    node = SLIST_FIRST(&incantation->players);
    send_graphical_event(server, "%s %zu %zu %d%s", \
        GRAPHICAL_PLAYER_INCANTATION_END, node->pos->x, node->pos->y, \
            done, LINE_BREAK);
    if (!done)
        end_incantation_error(server, incantation);
    else
        end_incantation_success(server, incantation, node->pos);
    SLIST_FOREACH(node, &incantation->players, next_incantation) {
        node->incantation = NULL;
    }
}
