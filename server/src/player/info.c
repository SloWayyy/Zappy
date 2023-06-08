/*
** EPITECH PROJECT, 2023
** server
** File description:
** info.c
*/

#include <stddef.h>

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
}

void inventory_handler(UNUSED server_t *server, client_t *client, \
    UNUSED char *line)
{
    schedule_action(client, &inventory_callback, INVENTORY_DELAY, NULL);
}

void slots_handler(UNUSED server_t *server, client_t *client, UNUSED char *line)
{
    append_buffer(client->buffer_out, "%d%s", client->player->team->slots, \
        LINE_BREAK);
}
