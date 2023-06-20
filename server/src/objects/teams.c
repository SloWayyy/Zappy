/*
** EPITECH PROJECT, 2023
** server
** File description:
** teams.c
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/queue.h>

#include "objects.h"
#include "types.h"
#include "util.h"

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

static bool init_eggs(server_t *server, team_t *team)
{
    int x = 0;
    int y = 0;
    egg_t *egg = NULL;

    for (size_t i = 0; i < team->slots; i++) {
        x = rand() % server->options->width;
        y = rand() % server->options->height;
        egg = new_egg(team, &server->zappy->map[y][x]);
        if (egg == NULL) {
            perror("malloc failed");
            return false;
        }
        egg->immortal = true;
        SLIST_INSERT_HEAD(team->eggs, egg, next_team);
        SLIST_INSERT_HEAD(&server->zappy->map[y][x].eggs, egg, next_tile);
    }
    return true;
}

team_t *new_team(server_t *server, char const *name, size_t capacity)
{
    team_t *new = malloc(sizeof(team_t));
    struct player_list *players = malloc(sizeof(struct player_list));
    struct egg_list *eggs = malloc(sizeof(struct egg_list));

    if (new == NULL || players == NULL || eggs == NULL) {
        perror("malloc failed");
        free_all(3, new, players, eggs);
        return NULL;
    }
    new->name = name;
    new->slots = capacity;
    new->players = players;
    new->eggs = eggs;
    SLIST_INIT(new->players);
    SLIST_INIT(new->eggs);
    if (!init_eggs(server, new)) {
        free_team(new);
        return NULL;
    }
    return new;
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
