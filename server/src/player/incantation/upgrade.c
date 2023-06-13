/*
** EPITECH PROJECT, 2023
** server
** File description:
** upgrade.c
*/

#include <stdbool.h>
#include <stddef.h>
#include <sys/queue.h>

#include "constants.h"
#include "graphical.h"
#include "player.h"
#include "types.h"
#include "util.h"

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

static void end_incantation_success(server_t *server, \
    incantation_t *incantation, tile_t *tile)
{
    player_t *node = NULL;
    client_t *target = NULL;

    for (size_t i = 0; i < RESOURCES_TYPES_QUANTITY; i++) {
        tile->resources[i] -= incantation->requirements->resources[i];
    }
    SLIST_FOREACH(node, &incantation->players, next_incantation) {
        target = get_client_by_player_id(server, node->id);
        node->level += 1;
        if (target != NULL) {
            append_buffer(target->buffer_out, "%s %zu%s", \
                PLAYER_ELEVATION_END, node->level, LINE_BREAK);
            flush_command(server, target);
        }
    }
}

void incantation_callback(server_t *server, UNUSED client_t *client, void *arg)
{
    incantation_t *incantation = (incantation_t *) arg;
    bool done = meet_requirements(incantation);
    player_t *node = NULL;

    if (SLIST_EMPTY(&incantation->players)) {
        return;
    }
    send_graphical_event(server, "%s %zu %zu %d%s", \
        GRAPHICAL_PLAYER_INCANTATION_START, node->pos->x, node->pos->y, \
        done, LINE_BREAK);
    if (!done) {
        end_incantation_error(server, incantation);
    } else {
        end_incantation_success(server, incantation, node->pos);
    }
    SLIST_FOREACH(node, &incantation->players, next_incantation) {
        node->incantation = NULL;
        node->next_incantation.sle_next = NULL;
    }
}
