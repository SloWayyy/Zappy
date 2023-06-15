/*
** EPITECH PROJECT, 2023
** server
** File description:
** players.c
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/queue.h>

#include "player.h"
#include "resources.h"
#include "types.h"
#include "constants.h"

static bool init_command_queue(player_t *new)
{
    new->commands = malloc(sizeof(command_queue_t));
    if (new->commands == NULL) {
        perror("malloc failed");
        return false;
    }
    STAILQ_INIT(new->commands);
    return true;
}

player_t *new_player(void)
{
    static size_t next_id = 0;
    player_t *new = malloc(sizeof(player_t));

    if (new == NULL) {
        perror("malloc failed");
        return NULL;
    }
    memset(new, 0, sizeof(player_t));
    new->id = next_id++;
    new->level = 1;
    new->direction = rand() % 4;
    memset(new->inventory, 0, sizeof(new->inventory));
    new->inventory[FOOD] = FOOD_DEFAULT;
    if (!init_command_queue(new)) {
        free(new);
        return NULL;
    }
    return new;
}

static void free_player_nodes(player_t *player)
{
    if (player->team != NULL) {
        if (!player->from_egg) {
            player->team->slots++;
        }
        SLIST_REMOVE(player->team->players, player, player, next_team);
    }
    if (player->pos != NULL) {
        SLIST_REMOVE(&player->pos->players, player, player, next_tile);
    }
    if (player->incantation != NULL) {
        SLIST_REMOVE(&player->incantation->players, player, player, \
            next_incantation);
    }
}

void free_player(player_t *player)
{
    command_t *command = NULL;

    free_player_nodes(player);
    while (!STAILQ_EMPTY(player->commands)) {
        command = STAILQ_FIRST(player->commands);
        STAILQ_REMOVE_HEAD(player->commands, next);
        free(command->command);
        free(command);
    }
    free(player->commands);
    free(player);
}
