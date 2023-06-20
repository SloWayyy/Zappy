/*
** EPITECH PROJECT, 2023
** server
** File description:
** magic.c
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/queue.h>

#include "buffer.h"
#include "player.h"
#include "resources.h"
#include "tasks.h"
#include "types.h"

static void select_players(server_t *server, incantation_t *incantation, \
    size_t size)
{
    int nb = 0;
    player_t *node = NULL;

    while (size >= incantation->requirements->players_nb) {
        nb = rand() % size;
        node = SLIST_FIRST(&incantation->players);
        for (int i = 0; i < nb; i++) {
            node = SLIST_NEXT(node, next_incantation);
        }
        SLIST_REMOVE(&incantation->players, node, player, next_incantation);
        size--;
        debug(server, "Too much players for incantation, removing player %d", \
            node->id);
    }
}

static void fill_players(server_t *server, incantation_t *incantation, \
    player_t *player)
{
    bool join = false;
    size_t size = 0;
    player_t *node = NULL;

    if (incantation->requirements->players_nb == 1) {
        SLIST_INSERT_HEAD(&incantation->players, player, next_incantation);
        return;
    }
    SLIST_FOREACH(node, &player->pos->players, next_tile) {
        join = node != player && node->level == player->level;
        if (join && !node->action_task->running && node->incantation == NULL) {
            SLIST_INSERT_HEAD(&incantation->players, node, next_incantation);
            size++;
            debug(server, "Player %d eligible for incantation", node->id);
        }
    }
    select_players(server, incantation, size);
    SLIST_INSERT_HEAD(&incantation->players, player, next_incantation);
}

incantation_t *setup_incantation(server_t *server, player_t *player, \
    const incantation_requirements_t *requirements)
{
    incantation_t *incantation = malloc(sizeof(incantation_t));

    if (incantation == NULL) {
        perror("malloc failed");
        return NULL;
    }
    debug(server, "Incantation initiated by player %d", player->id);
    incantation->requirements = requirements;
    SLIST_INIT(&incantation->players);
    fill_players(server, incantation, player);
    return incantation;
}

static bool meet_player_requirements(server_t *server, \
    incantation_t *incantation, player_t *leader)
{
    player_t *node = NULL;
    size_t size = 0;

    SLIST_FOREACH(node, &incantation->players, next_incantation) {
        if (node->pos != leader->pos || node->level != leader->level) {
            debug(server, "Incantation requirements failed: player %d has" \
                "a different position (%zu %zu) or level (%zu)", node->id, \
                node->pos->x, node->pos->y, node->level);
            debug(server, "Leader is at position (%zu %zu) and level %zu", \
                leader->pos->x, leader->pos->y, leader->level);
            return false;
        }
        size++;
    }
    if (size != incantation->requirements->players_nb) {
        debug(server, "Incantation requirements failed: %zu players died", \
            incantation->requirements->players_nb - size);
        return false;
    }
    return true;
}

bool meet_requirements(server_t *server, incantation_t *incantation)
{
    player_t *leader = SLIST_FIRST(&incantation->players);
    size_t required = 0;

    if (SLIST_EMPTY(&incantation->players)) {
        debug(server, "Incantation requirements failed: All players died");
        return false;
    }
    if (!meet_player_requirements(server, incantation, leader))
        return false;
    for (size_t i = 0; i < RESOURCES_TYPES_QUANTITY; i++) {
        required = incantation->requirements->resources[i];
        if (leader->pos->resources[i] < required) {
            required -= leader->pos->resources[i];
            debug(server,"Incantation requirements failed: %d %s missing", \
                required, RESOURCES[i].name);
            return false;
        }
    }
    debug(server, "Incantation requirements success");
    return true;
}
