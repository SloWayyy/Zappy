/*
** EPITECH PROJECT, 2023
** server
** File description:
** info.c
*/

#include <stdbool.h>

#include "constants.h"
#include "graphical.h"
#include "player.h"
#include "util.h"

static void send_graphical_item_event(server_t *server, client_t *client, \
    bool take, size_t resource_id)
{
    char *action = take ? GRAPHICAL_PLAYER_TAKE : GRAPHICAL_PLAYER_SET;

    send_graphical_event(server, "%s %zu %zu%s%s %zu %zu %zu", action, \
        client->player->id, resource_id, LINE_BREAK, \
        GRAPHICAL_PLAYER_INVENTORY, client->player->id, \
        client->player->pos->x, client->player->pos->y);
    for (size_t i = 0; i < RESOURCES_TYPES_QUANTITY; i++) {
        send_graphical_event(server, " %zu", client->player->inventory[i]);
    }
    send_graphical_event(server, "%s%s %zu %zu", LINE_BREAK, \
        GRAPHICAL_TILE_CONTENT, client->player->pos->x, client->player->pos->y);
    for (size_t i = 0; i < RESOURCES_TYPES_QUANTITY; i++) {
        send_graphical_event(server, " %zu", \
            client->player->pos->resources[i]);
    }
    send_graphical_event(server, "%s", LINE_BREAK);
}

void set_callback(server_t *server, client_t *client, void *arg)
{
    size_t *ptr = (size_t *) arg;

    if (client->player->inventory[*ptr] == 0) {
        append_buffer(client->buffer_out, "%s%s", PLAYER_KO, LINE_BREAK);
    } else {
        client->player->inventory[*ptr] -= 1;
        client->player->pos->resources[*ptr] += 1;
        send_graphical_item_event(server, client, false, *ptr);
        append_buffer(client->buffer_out, "%s%s", PLAYER_OK, LINE_BREAK);
    }
    flush_command(server, client);
}

void take_callback(server_t *server, client_t *client, void *arg)
{
    size_t *ptr = (size_t *) arg;

    if (client->player->pos->resources[*ptr] == 0) {
        append_buffer(client->buffer_out, "%s%s", PLAYER_KO, LINE_BREAK);
    } else {
        client->player->pos->resources[*ptr] -= 1;
        client->player->inventory[*ptr] += 1;
        send_graphical_item_event(server, client, true, *ptr);
        append_buffer(client->buffer_out, "%s%s", PLAYER_OK, LINE_BREAK);
    }
    flush_command(server, client);
}
