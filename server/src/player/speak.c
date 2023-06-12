/*
** EPITECH PROJECT, 2023
** server
** File description:
** speak.c
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "player.h"
#include "server.h"
#include "types.h"

static void broadcast_callback(server_t *server, client_t *client, void *arg)
{

}

bool broadcast_handler(server_t *server, client_t *client, char *line)
{
    char *message = NULL;
    size_t len = strlen(line);
    size_t prefix = strlen(PLAYER_BROADCAST);
    size_t message_len = len - prefix;

    if (len < strlen(PLAYER_BROADCAST) + 2) {
        return false;
    }
    message = malloc(sizeof(char) * message_len);
    strcpy(message, &line[prefix + 1]);
    message[message_len - 1] = '\0';
    setup_task(client->player->action_task, &broadcast_callback, message);
    schedule_task(client->player->action_task, server, BROADCAST_DELAY, 1);
    return true;
}
