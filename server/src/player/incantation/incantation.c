/*
** EPITECH PROJECT, 2023
** server
** File description:
** incantation.c
*/

#include <stdbool.h>
#include <stddef.h>
#include <sys/queue.h>

#include "constants.h"
#include "graphical.h"
#include "player.h"
#include "types.h"

static void send_graphical_incantation(server_t *server, \
    incantation_t *incantation)
{
    player_t *node = NULL;
    player_t *leader = SLIST_FIRST(&incantation->players);
    send_graphical_event(server, "%s %zu %zu %zu", \
        GRAPHICAL_PLAYER_INCANTATION_START, leader->pos->x, leader->pos->y, \
        leader->level);
    SLIST_FOREACH(node, &incantation->players, next_incantation) {
        send_graphical_event(server, " %zu", node->id);
    }
    send_graphical_event(server, "%s", LINE_BREAK);
}

bool incantation_handler(server_t *server, client_t *client, UNUSED char *line)
{
    const incantation_requirements_t *requirements = NULL;
    incantation_t *incantation = NULL;
    bool done = false;

    for (size_t i = 0; i < INCANTATIONS_COUNT && requirements == NULL; i++) {
        if (INCANTATIONS[i].level == client->player->level) {
            requirements = &INCANTATIONS[i];
        }
    }
    if (requirements == NULL) {
        return false;
    }
    incantation = setup_incantation(client->player, requirements);
    if (incantation == NULL) {
        return false;
    }
    done = start_incantation(server, client, incantation);
    if (done)
        send_graphical_incantation(server, incantation);
    return done;
}
