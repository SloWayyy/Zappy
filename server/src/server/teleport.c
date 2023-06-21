/*
** EPITECH PROJECT, 2023
** server
** File description:
** teleport.c
*/

#include <stdbool.h>
#include <string.h>
#include <sys/queue.h>

#include "buffer.h"
#include "commands.h"
#include "graphical.h"
#include "server.h"
#include "types.h"
#include "constants.h"

static void teleport_player(server_t *server, player_t *source, tile_t *dest, \
    direction_type_t direction)
{
    SLIST_REMOVE(&source->pos->players, source, player, next_tile);
    source->pos = dest;
    SLIST_INSERT_HEAD(&dest->players, source, next_tile);
    source->direction = direction;
    append_buffer(server->data->stdout_buffer, SERVER_TP_FORMAT, \
        source->id, dest->x, dest->y, LINE_BREAK);
    send_graphical_position_event(server, source);
}

static void teleport_players(server_t *server, player_t *source, tile_t *dest, \
    direction_type_t *ptr)
{
    client_t *node = NULL;
    direction_type_t direction = NORTH;

    if (source == NULL) {
        SLIST_FOREACH(node, server->clients, next) {
            if (node->type == PLAYER) {
                direction = ptr == NULL ? node->player->direction : *ptr;
                teleport_player(server, node->player, dest, direction);
            }
        }
        return;
    }
    if (ptr == NULL) {
        direction = source->direction;
    }
    teleport_player(server, source, dest, direction);
}

static tile_t *get_player_destination(server_t *server, char *target, \
    direction_type_t **direction)
{
    player_t *source = NULL;
    bool done = get_source(server, target, &source);

    if (!done) {
        append_buffer(server->data->stdout_buffer, "%s %s%s", \
            SERVER_PLAYER_ERROR, target, LINE_BREAK);
        return NULL;
    } else if (source == NULL) {
        append_buffer(server->data->stdout_buffer, "%s%s", \
            SERVER_TP_ERROR, LINE_BREAK);
        return NULL;
    }
    *direction = &source->direction;
    return source->pos;
}

static tile_t *get_destination(server_t *server, char *dest_x, char *dest_y, \
    direction_type_t **direction)
{
    int x = 0;
    int y = 0;
    bool neg = false;

    if (dest_y == NULL) {
        return get_player_destination(server, dest_x, direction);
    }
    if (!check_number(dest_x, &x) || !check_number(dest_y, &y)) {
        append_buffer(server->data->stdout_buffer, "%s%s", \
            SERVER_TP_COORD_USAGE, LINE_BREAK);
        return NULL;
    }
    neg = x < 0 || y < 0;
    if (neg || x >= server->options->width || y >= server->options->height) {
        append_buffer(server->data->stdout_buffer, "%s%s", \
            SERVER_TP_ERROR, LINE_BREAK);
        return NULL;
    }
    return &server->zappy->map[y][x];
}

void tp_handler(server_t *server)
{
    char *args[4];
    player_t *player = NULL;
    tile_t *dest = NULL;
    direction_type_t *direction = NULL;

    for (int i = 0; i < 4; i++)
        args[i] = strtok(NULL, " ");
    if (args[0] == NULL || args[1] == NULL || args[3] != NULL) {
        append_buffer(server->data->stdout_buffer, "%s%s%s%s", \
            SERVER_TP_PLAYER_USAGE, LINE_BREAK, \
            SERVER_TP_COORD_USAGE, LINE_BREAK);
        return;
    } else if (!get_source(server, args[0], &player)) {
        append_buffer(server->data->stdout_buffer, "%s %s%s", \
            SERVER_PLAYER_ERROR, args[0], LINE_BREAK);
        return;
    }
    dest = get_destination(server, args[1], args[2], &direction);
    if (dest != NULL)
        teleport_players(server, player, dest, direction);
}
