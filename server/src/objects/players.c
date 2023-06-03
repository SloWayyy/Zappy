/*
** EPITECH PROJECT, 2023
** server
** File description:
** players.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/queue.h>

#include "types.h"

player_t *new_player(void)
{
    player_t *new = malloc(sizeof(player_t));

    if (new == NULL) {
        perror("malloc failed");
        return NULL;
    }
    new->team = NULL;
    new->level = 1;
    new->food_ticks = 0;
    memset(new->inventory, 0, sizeof(new->inventory));
    return new;
}

void free_player(player_t *player)
{
    team_t *team = player->team;

    if (team != NULL) {
        team->slots++;
        SLIST_REMOVE(team->players, player, player, next_team);
    }
    free(player);
}
