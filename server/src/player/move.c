/*
** EPITECH PROJECT, 2023
** server
** File description:
** move.c
*/

#include <stdbool.h>
#include <stddef.h>
#include <sys/queue.h>

#include "constants.h"
#include "graphical.h"
#include "player.h"
#include "server.h"
#include "types.h"
#include "util.h"

vector_t get_direction(direction_type_t direction)
{
    vector_t vector = {0, 0 };

    switch (direction) {
        case NORTH:
            vector.y = -1;
            break;
        case EAST:
            vector.x = 1;
            break;
        case SOUTH:
            vector.y = 1;
            break;
        case WEST:
            vector.x = -1;
            break;
    }
    return vector;
}

static void forward_callback(server_t *server, client_t *client, \
    UNUSED void *arg)
{
    vector_t vector = get_direction(client->player->direction);
    int pos_x = (int) client->player->pos->x + vector.x;
    int pos_y = (int) client->player->pos->y + vector.y;

    pos_x = (pos_x + server->options->width) % server->options->width;
    pos_y = (pos_y + server->options->height) % server->options->height;
    SLIST_REMOVE(&client->player->pos->players, client->player, player, \
        next_tile);
    client->player->pos = &server->zappy->map[pos_y][pos_x];
    SLIST_INSERT_HEAD(&client->player->pos->players, client->player, next_tile);
    send_graphical_position_event(server, client);
    append_buffer(client->buffer_out, "%s%s", PLAYER_OK, LINE_BREAK);
    flush_command(server, client);
}

bool forward_handler(server_t *server, client_t *client, UNUSED char *line)
{
    setup_task(client->player->action_task, &forward_callback, NULL);
    schedule_task(client->player->action_task, server, FORWARD_DELAY, 1);
    return true;
}
