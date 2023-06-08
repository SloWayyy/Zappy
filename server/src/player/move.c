/*
** EPITECH PROJECT, 2023
** server
** File description:
** move.c
*/

#include <sys/queue.h>

#include "constants.h"
#include "graphical.h"
#include "player.h"
#include "server.h"
#include "types.h"
#include "util.h"

static vector_t get_direction(direction_type_t direction)
{
    vector_t vector = {0, 0};

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

    if (pos_x < 0) {
        pos_x += server->options->width;
    }
    if (pos_y < 0) {
        pos_y += server->options->height;
    }
    pos_x %= server->options->width;
    pos_y %= server->options->height;
    SLIST_REMOVE(&client->player->pos->players, client->player, player, \
        next_tile);
    client->player->pos = &server->zappy->map[pos_y][pos_x];
    SLIST_INSERT_HEAD(&client->player->pos->players, client->player, next_tile);
    flush_action(client->player);
    send_graphical_position_event(server, client);
    append_buffer(client->buffer_out, "%s%s", PLAYER_OK, LINE_BREAK);
}

void forward_handler(UNUSED server_t *server, client_t *client, \
    UNUSED char *line)
{
    schedule_action(client->player, &forward_callback, FORWARD_DELAY, NULL);
}
