/*
** EPITECH PROJECT, 2023
** server
** File description:
** level.c
*/

#include <string.h>

#include "buffer.h"
#include "commands.h"
#include "constants.h"
#include "graphical.h"
#include "server.h"
#include "types.h"

static void access_level(server_t *server, player_t *source, \
    int level)
{
    if (level == -1) {
        append_buffer(server->data->stdout_buffer, SERVER_LEVEL_INFO, \
            source->id, source->level, LINE_BREAK);
        return;
    }
    source->level = (size_t) level;
    append_buffer(server->data->stdout_buffer, SERVER_LEVEL_FORMAT, \
        source->id, source->level, LINE_BREAK);
    send_graphical_level_event(server, source);
}

static void access_levels(server_t *server, source_t *source, int level)
{
    client_t *node = NULL;

    if (source->all) {
        SLIST_FOREACH(node, server->clients, next) {
            if (node->type == PLAYER) {
                access_level(server, node->player, level);
            }
        }
        return;
    }
    access_level(server, source->player, level);
}

static bool get_level(server_t *server, char **args, int *level)
{
    int num = 0;

    if (args[1] == NULL) {
        *level = -1;
        return true;
    }
    if (!check_number(args[1], &num) || num < 1) {
        append_buffer(server->data->stdout_buffer, "%s%s", \
            SERVER_LEVEL_USAGE, LINE_BREAK);
        return false;
    }
    if (num > SERVER_LEVEL_LIMIT) {
        append_buffer(server->data->stdout_buffer, SERVER_LEVEL_ERROR, \
            SERVER_LEVEL_LIMIT, LINE_BREAK);
        return false;
    }
    *level = num;
    return true;
}

void level_handler(server_t *server)
{
    char *args[3];
    source_t source = { NULL, false, false };
    int level = 0;

    for (int i = 0; i < 3; i++) {
        args[i] = strtok(NULL, " ");
    }
    if (args[0] == NULL || args[2] != NULL) {
        append_buffer(server->data->stdout_buffer, "%s%s", \
            SERVER_GIVE_USAGE, LINE_BREAK);
        return;
    } else if (!get_source(server, args[0], &source)) {
        append_buffer(server->data->stdout_buffer, "%s %s%s", \
            SERVER_PLAYER_ERROR, args[0], LINE_BREAK);
        return;
    }
    if (get_level(server, args, &level)) {
        access_levels(server, &source, level);
    }
}
