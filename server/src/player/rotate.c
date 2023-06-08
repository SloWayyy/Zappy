/*
** EPITECH PROJECT, 2023
** server
** File description:
** rotate.c
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "constants.h"
#include "graphical.h"
#include "player.h"
#include "server.h"
#include "types.h"
#include "util.h"

static void rotate_callback(server_t *server, client_t *client, void *arg)
{
    bool *ptr = (bool *) arg;
    int velocity = *ptr ? 1 : -1;

    client->player->direction = (client->player->direction + velocity) % 4;
    free(arg);
    flush_action(client->player);
    send_graphical_position_event(server, client);
    append_buffer(client->buffer_out, "%s%s", PLAYER_OK, LINE_BREAK);
}

void left_handler(UNUSED server_t *server, client_t *client, UNUSED char *line)
{
    bool *dir = malloc(sizeof(bool));

    if (dir == NULL) {
        perror("malloc failed");
        return;
    }
    *dir = false;
    schedule_action(client, &rotate_callback, LEFT_DELAY, dir);
}

void right_handler(UNUSED server_t *server, client_t *client, UNUSED char *line)
{
    bool *dir = malloc(sizeof(bool));

    if (dir == NULL) {
        perror("malloc failed");
        return;
    }
    *dir = true;
    schedule_action(client, &rotate_callback, RIGHT_DELAY, dir);
}
