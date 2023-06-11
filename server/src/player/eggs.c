/*
** EPITECH PROJECT, 2023
** server
** File description:
** eggs.c
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/queue.h>

#include "constants.h"
#include "graphical.h"
#include "player.h"
#include "server.h"
#include "types.h"
#include "util.h"

static egg_t *new_egg(team_t *team, tile_t *tile)
{
    static size_t next_id = 0;
    egg_t *new = malloc(sizeof(egg_t));

    if (new == NULL) {
        perror("malloc failed");
        return NULL;
    }
    new->id = next_id++;
    new->team = team;
    new->pos = tile;
    return new;
}

static void fork_callback(server_t *server, client_t *client, UNUSED void *data)
{
    egg_t *egg = new_egg(client->player->team, client->player->pos);

    if (egg == NULL) {
        append_buffer(client->buffer_out, "%s%s", PLAYER_KO, LINE_BREAK);
        flush_command(server, client);
        return;
    }
    SLIST_INSERT_HEAD(client->player->team->eggs, egg, next_team);
    SLIST_INSERT_HEAD(&client->player->pos->eggs, egg, next_tile);
    send_graphical_event(server, "%s %zu%s%s %zu %zu %zu %zu%s", \
        GRAPHICAL_PLAYER_FORK, client->player->id, LINE_BREAK, \
        GRAPHICAL_PLAYER_EGG, egg->id, client->player->id, \
        egg->pos->x, egg->pos->y, LINE_BREAK);
    append_buffer(client->buffer_out, "%s%s", PLAYER_OK, LINE_BREAK);
    flush_command(server, client);
}

bool fork_handler(server_t *server, client_t *client, UNUSED char *line)
{
    setup_task(client->player->action_task, &fork_callback, NULL);
    schedule_task(client->player->action_task, server, FORK_DELAY, 1);
    return true;
}
