/*
** EPITECH PROJECT, 2023
** server
** File description:
** magic.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/queue.h>

#include "player.h"
#include "types.h"

static void fill_players(incantation_t *incantation, player_t *player)
{
    int nb = 0;
    size_t players = 0;
    player_t *node = NULL;

    SLIST_FOREACH(node, &player->pos->players, next_incantation) {
        if (node != player && node->next_incantation.sle_next == NULL) {
            SLIST_INSERT_HEAD(&incantation->players, node, next_incantation);
            players++;
        }
    }
    while (players >= incantation->requirements->players_nb) {
        nb = rand() % players;
        node = incantation->players.slh_first;
        for (int i = 0; i < nb; i++) {
            node = node->next_incantation.sle_next;
        }
        SLIST_REMOVE(&incantation->players, node, player, next_incantation);
        players--;
    }
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
    incantation->leader = player;
    incantation->requirements = requirements;
    SLIST_INIT(&incantation->players);
    fill_players(incantation, player);
    return incantation;
}
