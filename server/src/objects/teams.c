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

    if (new == NULL) {
        perror("malloc failed");
        return NULL;
    }
    new->name = name;
    new->capacity = capacity;
    new->slots = capacity;
    new->players = malloc(sizeof(struct player_list));
    if (new->players == NULL) {
        perror("malloc failed");
        free(new);
        return NULL;
    }
    SLIST_INIT(new->players);
    return new;
}

void free_team(team_t *team)
{
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
