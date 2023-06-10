/*
** EPITECH PROJECT, 2023
** server
** File description:
** info.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "constants.h"
#include "player.h"
#include "server.h"
#include "types.h"
#include "util.h"

void take_handler(server_t *server, client_t *client, char *line)
{
    size_t *index = malloc(sizeof(size_t));
    char *item = strtok(line, " ");

    if (index == NULL) {
        perror("malloc failed");
        return;
    }
    if (item == NULL || strtok(NULL, " ") != NULL) {
        append_buffer(client->buffer_out, "%s%s", PLAYER_KO, LINE_BREAK);
        return;
    }
    for (size_t i = 0; i < RESOURCES_TYPES_QUANTITY; i++) {
        if (strcmp(resources_map[i], item) == 0) {
            *index = i;
            setup_task(client->player->action_task, &take_callback, index);
            schedule_task(client->player->action_task, server, TAKE_DELAY, 1);
            return;
        }
    }
    append_buffer(client->buffer_out, "%s%s", PLAYER_KO, LINE_BREAK);
}

void set_handler(server_t *server, client_t *client, char *line)
{
    size_t *index = malloc(sizeof(size_t));
    char *item = strtok(line, " ");

    if (index == NULL) {
        perror("malloc failed");
        return;
    }
    if (item == NULL || strtok(NULL, " ") != NULL) {
        append_buffer(client->buffer_out, "%s%s", PLAYER_KO, LINE_BREAK);
        return;
    }
    for (size_t i = 0; i < RESOURCES_TYPES_QUANTITY; i++) {
        if (strcmp(resources_map[i], item) == 0) {
            *index = i;
            setup_task(client->player->action_task, &set_callback, index);
            schedule_task(client->player->action_task, server, SET_DELAY, 1);
            return;
        }
    }
    append_buffer(client->buffer_out, "%s%s", PLAYER_KO, LINE_BREAK);
}