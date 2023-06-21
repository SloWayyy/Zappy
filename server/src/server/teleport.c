/*
** EPITECH PROJECT, 2023
** server
** File description:
** teleport.c
*/

#include <stdbool.h>
#include <string.h>

#include "buffer.h"
#include "commands.h"
#include "constants.h"
#include "server.h"
#include "types.h"
#include "util.h"

static tile_t *get_player_destination(server_t *server, char *target, \
    direction_type_t **direction)
{
    source_t source = { NULL, false, false };
    bool done = get_source(server, target, &source);

    if (!done) {
        append_buffer(server->data->stdout_buffer, "%s %s%s", \
            SERVER_PLAYER_ERROR, target, LINE_BREAK);
        return NULL;
    } else if (source.player == NULL) {
        append_buffer(server->data->stdout_buffer, "%s%s", \
            SERVER_TP_ERROR, LINE_BREAK);
        return NULL;
    }
    *direction = &source.player->direction;
    return source.player->pos;
}

static bool get_coordinates(server_t *server, char **args, \
    source_t *source, vector_t *pos)
{
    vector_t vec = { 0, 0 };
    char *arg_x = args[1];
    char *arg_y = args[2];

    if (args[1][0] == '~' && source->player != NULL) {
        pos->x = source->player->pos->x;
        arg_x = &args[1][1];
    }
    if (args[2][0] == '~' && source->player != NULL) {
        pos->y = source->player->pos->y;
        arg_y = &args[2][1];
    }
    if (!check_number(arg_x, &vec.x) || !check_number(arg_y, &vec.y)) {
        append_buffer(server->data->stdout_buffer, "%s%s", \
            SERVER_TP_ERROR, LINE_BREAK);
        return false;
    }
    pos->x += vec.x;
    pos->y += vec.y;
    return true;
}

static tile_t *get_destination(server_t *server, char **args, \
    source_t *source, direction_type_t **direction)
{
    vector_t pos = { 0, 0 };

    if (args[2] == NULL) {
        return get_player_destination(server, args[1], direction);
    } else if (!get_coordinates(server, args, source, &pos)) {
        return NULL;
    }
    while (pos.x < 0) {
        pos.x += server->options->width;
    }
    while (pos.y < 0) {
        pos.y += server->options->height;
    }
    pos.x %= server->options->width;
    pos.y %= server->options->height;
    return &server->zappy->map[pos.y][pos.x];
}

void tp_handler(server_t *server)
{
    char *args[4];
    source_t source = { NULL, false, false };
    tile_t *dest = NULL;
    direction_type_t *direction = NULL;

    for (int i = 0; i < 4; i++)
        args[i] = strtok(NULL, " ");
    if (args[0] == NULL || args[1] == NULL || args[3] != NULL) {
        append_buffer(server->data->stdout_buffer, "%s%s%s%s", \
            SERVER_TP_PLAYER_USAGE, LINE_BREAK, \
            SERVER_TP_COORD_USAGE, LINE_BREAK);
        return;
    } else if (!get_source(server, args[0], &source)) {
        append_buffer(server->data->stdout_buffer, "%s %s%s", \
            SERVER_PLAYER_ERROR, args[0], LINE_BREAK);
        return;
    }
    dest = get_destination(server, args, &source, &direction);
    if (dest != NULL)
        teleport_players(server, &source, dest, direction);
}
