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
#include "tasks.h"
#include "types.h"

static tile_t *get_spawn_from_egg(server_t *server, team_t *team, \
    size_t size, size_t immortal)
{
    size_t i = 0;
    size_t num = rand() % (immortal < size ? size - immortal : size);
    egg_t *node = NULL;
    tile_t *tile = NULL;

    SLIST_FOREACH(node, team->eggs, next_team) {
        if (i == num) {
            tile = node->pos;
            send_graphical_event(server, "%s %zu%s", \
                GRAPHICAL_PLAYER_EGG_JOIN, node->id, LINE_BREAK);
            SLIST_REMOVE(team->eggs, node, egg, next_team);
            SLIST_REMOVE(&tile->eggs, node, egg, next_tile);
            free(node);
            return tile;
        }
        if (immortal == size || !node->immortal) {
            i++;
        }
    }
    return NULL;
}

static tile_t *get_spawn(server_t *server, team_t *team, player_t *player)
{
    size_t eggs = 0;
    size_t immortal = 0;
    egg_t *node = NULL;
    tile_t *spawn = NULL;
    int x = rand() % server->options->width;
    int y = rand() % server->options->height;

    SLIST_FOREACH(node, team->eggs, next_team) {
        eggs++;
        if (node->immortal) {
            immortal++;
        }
    }
    player->from_egg = eggs > 0 && immortal == 0;
    if (eggs > 0) {
        spawn = get_spawn_from_egg(server, team, eggs, immortal);
    }
    return spawn == NULL ? &server->zappy->map[y][x] : spawn;
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
    if (!server->options->immortal) {
        schedule_task(food_task, server, FOOD_CONSUME_TICKS, -1);
    }
    return true;
}

static bool join_team(server_t *server, client_t *client, team_t *team)
{
    tile_t *spawn = NULL;
    player_t *player = new_player();

    client->player = player;
    if (client->player == NULL) {
        perror("malloc failed");
        return false;
    } else if (!init_player_tasks(server, client)) {
        free_player(client->player);
        return false;
    }
    spawn = get_spawn(server, team, player);
    client->player->team = team;
    client->player->pos = spawn;
    team->slots -= player->from_egg ? 0 : 1;
    SLIST_INSERT_HEAD(team->players, client->player, next_team);
    SLIST_INSERT_HEAD(&spawn->players, client->player, next_tile);
    send_graphical_join_event(server, client);
    return true;
}

bool try_join_team(server_t *server, client_t *client, char *line)
{
    bool joinable = false;
    team_t *node = NULL;

    SLIST_FOREACH(node, server->zappy->teams, next) {
        joinable = !SLIST_EMPTY(node->eggs) || node->slots > 0;
        if (strcmp(line, node->name) == 0 && joinable) {
            return join_team(server, client, node);
        }
    }
    return false;
}
