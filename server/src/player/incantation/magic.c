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

#include "player.h"
#include "types.h"

static void select_players(incantation_t *incantation, size_t size)
{
    int nb = 0;
    player_t *node = NULL;

    while (size >= incantation->requirements->players_nb) {
        nb = rand() % size;
        node = SLIST_FIRST(&incantation->players);
        for (int i = 0; i < nb; i++) {
            node = node->next_incantation.sle_next;
        }
        SLIST_REMOVE(&incantation->players, node, player, next_incantation);
        size--;
    }
}

static void fill_players(incantation_t *incantation, player_t *player)
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
        }
    }
    select_players(incantation, size);
    SLIST_INSERT_HEAD(&incantation->players, player, next_incantation);
}

incantation_t *setup_incantation(player_t *player, \
    const incantation_requirements_t *requirements)
{
    incantation_t *incantation = malloc(sizeof(incantation_t));

    if (incantation == NULL) {
        perror("malloc failed");
        return NULL;
    }
    incantation->requirements = requirements;
    SLIST_INIT(&incantation->players);
    fill_players(incantation, player);
    return incantation;
}

bool meet_requirements(incantation_t *incantation)
{
    player_t *leader = NULL;
    player_t *node = NULL;
    size_t size = 0;

    if (SLIST_EMPTY(&incantation->players)) {
        return false;
    }
    leader = SLIST_FIRST(&incantation->players);
    for (size_t i = 0; i < RESOURCES_TYPES_QUANTITY; i++) {
        if (leader->pos->resources[i] < incantation->requirements->resources[i])
            return false;
    }
    SLIST_FOREACH(node, &incantation->players, next_incantation) {
        if (node->pos != leader->pos || node->level != leader->level) {
            return false;
        }
        size++;
    }
    return size == incantation->requirements->players_nb;
}
