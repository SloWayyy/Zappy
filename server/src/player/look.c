/*
** EPITECH PROJECT, 2023
** server
** File description:
** look.c
*/

#include <stddef.h>
#include <sys/queue.h>

#include "constants.h"
#include "player.h"
#include "server.h"
#include "types.h"
#include "util.h"

static void dump_tile(tile_t *tile, client_t *client)
{
    char *separator = "";
    player_t *node = NULL;

    SLIST_FOREACH(node, &tile->players, next_tile) {
        append_buffer(client->buffer_out, "%s%s", separator, "player");
        separator = " ";
    }
    for (size_t i = 0; i < RESOURCES_TYPES_QUANTITY; i++) {
        for (size_t j = 0; j < tile->resources[i] || j < 2; j++) {
            append_buffer(client->buffer_out, "%s%s", \
                separator, resources_map[i]);
            separator = " ";
        }
    }
}

static void dump_line(server_t *server, client_t *client, size_t line, \
    vector_t *velocity)
{
    size_t tiles = line * 2 + 1;
    vector_t left = get_direction( (client->player->direction - 1) % 4);
    vector_t right = { left.x * -1, left.y * -1 };
    int x = ((int) client->player->pos->x + server->options->width + \
        velocity->x * line + left.x * line) % server->options->width;
    int y = ((int) client->player->pos->y + server->options->height + \
        velocity->y * line + left.y * line) % server->options->width;

    for (size_t i = 0; i < tiles; i++) {
        if (i > 0) {
            append_buffer(client->buffer_out, ",");
        }
        dump_tile(&server->zappy->map[y][x], client);
        x = (x + right.x + server->options->width) % server->options->width;
        y = (y + right.y + server->options->height) % server->options->height;
    }
}

void look_callback(server_t *server, client_t *client, UNUSED void *arg)
{
    vector_t velocity = get_direction(client->player->direction);

    append_buffer(client->buffer_out, "[");
    for (size_t i = 0; i <= client->player->level; i++) {
        if (i > 0) {
            append_buffer(client->buffer_out, ",");
        }
        dump_line(server, client, i, &velocity);
    }
    append_buffer(client->buffer_out, "]%s", LINE_BREAK);
    flush_command(server, client);
}

void look_handler(server_t *server, client_t *client, UNUSED char *line)
{
    setup_task(client->player->action_task, &look_callback, NULL);
    schedule_task(client->player->action_task, server, LOOK_DELAY, 1);
}
