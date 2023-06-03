/*
** EPITECH PROJECT, 2023
** server
** File description:
** team_join.c
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/queue.h>

#include "objects.h"
#include "types.h"

static tile_t *get_spawn(server_t *server, team_t *team)
{
    (void) team;
    int x = rand() % server->options->width;
    int y = rand() % server->options->height;

    return &server->zappy->map[y][x];
}

static bool join_team(server_t *server, client_t *client, team_t *team)
{
    tile_t *spawn = get_spawn(server, team);

    client->player = new_player();
    if (client->player == NULL) {
        perror("malloc failed");
        return false;
    }
    client->player->team = team;
    client->player->pos = spawn;
    team->slots--;
    SLIST_INSERT_HEAD(team->players, client->player, next_team);
    SLIST_INSERT_HEAD(&spawn->players, client->player, next_tile);
    return true;
}

static bool can_join(team_t *team)
{
    if (team->slots == 0) {
        return false;
    }
    return true;
}

bool try_join_team(server_t *server, client_t *client, char *line)
{
    team_t *node = NULL;

    SLIST_FOREACH(node, server->zappy->teams, next) {
        if (strcmp(line, node->name) == 0 && can_join(node)) {
            return join_team(server, client, node);
        }
    }
    return false;
}
