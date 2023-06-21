/*
** EPITECH PROJECT, 2023
** server
** File description:
** give.c
*/

#include <stdbool.h>
#include <string.h>
#include <sys/queue.h>

#include "buffer.h"
#include "commands.h"
#include "constants.h"
#include "graphical.h"
#include "server.h"
#include "types.h"
#include "resources.h"

static void give_item(server_t *server, player_t *source, \
    size_t index, size_t amount)
{
    source->inventory[index] += amount;
    append_buffer(server->data->stdout_buffer, SERVER_GIVE_FORMAT, \
        source->id, RESOURCES[index].name, amount, LINE_BREAK);
    send_graphical_inventory_event(server, source);
}

static void give_items(server_t *server, source_t *source, \
    size_t index, size_t amount)
{
    client_t *node = NULL;

    if (source->all) {
        SLIST_FOREACH(node, server->clients, next) {
            if (node->type == PLAYER) {
                give_item(server, node->player, index, amount);
            }
        }
        return;
    }
    give_item(server, source->player, index, amount);
}

static bool get_item_amount(server_t *server, char **args, size_t *amount)
{
    int num = 0;

    if (args[2] == NULL) {
        *amount = 1;
        return true;
    }
    if (!check_number(args[2], &num) || num < 1 || num > SERVER_GIVE_LIMIT) {
        append_buffer(server->data->stdout_buffer, "%s%s", \
            SERVER_GIVE_USAGE, LINE_BREAK);
        return false;
    }
    *amount = (size_t) num;
    return true;
}

static bool get_item(server_t *server, char **args, \
    size_t *index, size_t *amount)
{
    bool done = false;

    for (size_t i = 0; i < RESOURCES_TYPES_QUANTITY && !done; i++) {
        if (strcmp(args[1], RESOURCES[i].name) == 0) {
            *index = i;
            done = true;
        }
    }
    if (!done) {
        append_buffer(server->data->stdout_buffer, "%s%s", \
            SERVER_RESOURCE_ERROR, LINE_BREAK);
        return false;
    }
    return get_item_amount(server, args, amount);
}

void give_handler(server_t *server)
{
    char *args[4];
    source_t source = { NULL, false, false };
    size_t index = 0;
    size_t count = 0;

    for (int i = 0; i < 4; i++) {
        args[i] = strtok(NULL, " ");
    }
    if (args[0] == NULL || args[1] == NULL || args[3] != NULL) {
        append_buffer(server->data->stdout_buffer, "%s%s", \
            SERVER_GIVE_USAGE, LINE_BREAK);
        return;
    } else if (!get_source(server, args[0], &source)) {
        append_buffer(server->data->stdout_buffer, "%s %s%s", \
            SERVER_PLAYER_ERROR, args[0], LINE_BREAK);
        return;
    }
    if (get_item(server, args, &index, &count)) {
        give_items(server, &source, index, count);
    }
}
