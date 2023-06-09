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

#include "constants.h"
#include "graphical.h"
#include "objects.h"
#include "player.h"
#include "server.h"
#include "types.h"

static tile_t *get_spawn(server_t *server, team_t *team)
{
    (void) team;
    int x = rand() % server->options->width;
    int y = rand() % server->options->height;

    return &server->zappy->map[y][x];
}

static bool init_player_tasks(server_t *server, client_t *client)
{
    task_t *food_task = register_task(server, client, &food_callback);

    if (food_task == NULL) {
        return false;
    }
    client->player->action_task = register_task(server, client, NULL);
    if (client->player->action_task == NULL) {
        SLIST_REMOVE(server->tasks, food_task, task, next);
        free(food_task);
        return false;
    }
    schedule_task(food_task, server, FOOD_CONSUME_TICKS, -1);
    return true;
}

static bool join_team(server_t *server, client_t *client, team_t *team)
{
    tile_t *spawn = get_spawn(server, team);
    player_t *player = new_player();

    client->player = player;
    if (client->player == NULL) {
        perror("malloc failed");
        return false;
    } else if (!init_player_tasks(server, client)) {
        free_player(client->player);
        return false;
    }
    client->player->team = team;
    client->player->pos = spawn;
    team->slots--;
    SLIST_INSERT_HEAD(team->players, client->player, next_team);
    SLIST_INSERT_HEAD(&spawn->players, client->player, next_tile);
    send_graphical_event(server, "%s %zu %zu %zu %zu %zu %s%s", \
        GRAPHICAL_PLAYER_JOIN, player->id, player->pos->x, player->pos->y, \
        player->direction, player->level, player->team->name, LINE_BREAK);
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
