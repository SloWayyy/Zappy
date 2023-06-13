/*
** EPITECH PROJECT, 2023
** server
** File description:
** info.c
*/

#include <stdbool.h>
#include <stddef.h>
#include <sys/queue.h>

#include "constants.h"
#include "player.h"
#include "server.h"
#include "types.h"
#include "util.h"

static void inventory_callback(UNUSED server_t *server, client_t *client, \
    UNUSED void *arg)
{
    append_buffer(client->buffer_out, "[");
    for (int i = 0; i < RESOURCES_TYPES_QUANTITY; i++) {
        if (i > 0) {
            append_buffer(client->buffer_out, ", ");
        }
        append_buffer(client->buffer_out, "%s %d", \
            resources_map[i], client->player->inventory[i]);
    }
    append_buffer(client->buffer_out, "]%s", LINE_BREAK);
    flush_command(server, client);
}

bool inventory_handler(UNUSED server_t *server, client_t *client, \
    UNUSED char *line)
{
    setup_task(client->player->action_task, &inventory_callback, NULL);
    schedule_task(client->player->action_task, server, INVENTORY_DELAY, 1);
    return true;
}

static void slots_callback(UNUSED server_t *server, client_t *client, \
    UNUSED void *arg)
{
    size_t slots = client->player->team->slots;
    egg_t *node = NULL;

    SLIST_FOREACH(node, client->player->team->eggs, next_team) {
        slots++;
    }
    append_buffer(client->buffer_out, "%d%s", slots, LINE_BREAK);
    flush_command(server, client);
}

bool slots_handler(UNUSED server_t *server, client_t *client, UNUSED char *line)
{
    setup_task(client->player->action_task, &slots_callback, NULL);
    schedule_task(client->player->action_task, server, SLOTS_DELAY, 1);
    return true;
}
