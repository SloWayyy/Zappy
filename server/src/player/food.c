/*
** EPITECH PROJECT, 2023
** server
** File description:
** food.c
*/

#include <stdbool.h>
#include <stddef.h>
#include <sys/queue.h>

#include "constants.h"
#include "graphical.h"
#include "player.h"
#include "types.h"
#include "util.h"

void food_callback(UNUSED server_t *server, client_t *client, UNUSED void *arg)
{
    task_t *node = NULL;

    if (client->player->inventory[FOOD] > 0) {
        client->player->inventory[FOOD] -= 1;
        return;
    }
    append_buffer(client->buffer_out, "%s%s", PLAYER_DEATH, LINE_BREAK);
    client->player->dead = true;
    SLIST_FOREACH(node, server->tasks, next) {
        if (node->client == client) {
            node->running = false;
        }
    }
    send_graphical_event(server, "%s %zu%s", GRAPHICAL_PLAYER_DEATH, \
        client->player->id, LINE_BREAK);
}
