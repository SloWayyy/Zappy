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
    static size_t next_id = 0;
    player_t *new = malloc(sizeof(player_t));

    if (new == NULL) {
        perror("malloc failed");
        return NULL;
    }
    new->id = next_id++;
    new->level = 1;
    new->team = NULL;
    new->pos = NULL;
    new->direction = rand() % 4;
    memset(new->inventory, 0, sizeof(new->inventory));
    return new;
}

void free_player(player_t *player)
{
    if (player->team != NULL) {
        player->team->slots++;
        SLIST_REMOVE(player->team->players, player, player, next_team);
    }
    if (player->pos != NULL) {
        SLIST_REMOVE(&player->pos->players, player, player, next_tile);
    }
    free(player);
}
