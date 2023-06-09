/*
** EPITECH PROJECT, 2023
** server
** File description:
** teams.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/queue.h>

#include "types.h"

team_t *new_team(char const *name, size_t capacity)
{
    team_t *new = malloc(sizeof(team_t));
    struct player_list *players = malloc(sizeof(struct player_list));
    struct egg_list *eggs = malloc(sizeof(struct egg_list));

    if (new == NULL || players == NULL || eggs == NULL) {
        perror("malloc failed");
        free(new);
        free(players);
        free(eggs);
        return NULL;
    }
    new->name = name;
    new->slots = capacity;
    new->players = players;
    new->eggs = eggs;
    SLIST_INIT(new->players);
    SLIST_INIT(new->eggs);
    return new;
}

void free_team(team_t *team)
{
    egg_t *node = NULL;

    while (!SLIST_EMPTY(team->eggs)) {
        node = SLIST_FIRST(team->eggs);
        SLIST_REMOVE_HEAD(team->eggs, next_team);
        free(node);
    }
    free(team->eggs);
    free(team->players);
    free(team);
}

void free_teams(server_t *server)
{
    team_t *node = NULL;

    while (!SLIST_EMPTY(server->zappy->teams)) {
        node = SLIST_FIRST(server->zappy->teams);
        SLIST_REMOVE_HEAD(server->zappy->teams, next);
        free_team(node);
    }
}
