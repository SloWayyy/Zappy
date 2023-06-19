/*
** EPITECH PROJECT, 2023
** server
** File description:
** items_callback.cpp
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "player.h"
#include "resources.h"
#include "tasks.h"
#include "types.h"
#include "constants.h"

static char *get_resource_name(char *line)
{
    char *str = strtok(line, " ");

    if (str == NULL) {
        return NULL;
    }
    str = strtok(NULL, " ");
    if (str == NULL || strtok(NULL, " ") != NULL) {
        return NULL;
    }
    return str;
}

bool set_handler(server_t *server, client_t *client, char *line)
{
    size_t *index = NULL;
    char *item = get_resource_name(line);

    if (item == NULL)
        return false;
    index = malloc(sizeof(size_t));
    if (index == NULL) {
        perror("malloc failed");
        return false;
    }
    for (size_t i = 0; i < RESOURCES_TYPES_QUANTITY; i++) {
        if (strcmp(RESOURCES[i].name, item) == 0) {
            *index = i;
            setup_task(client->player->action_task, &set_callback, index);
            schedule_task(client->player->action_task, server, SET_DELAY, 1);
            return true;
        }
    }
    free(index);
    return false;
}

bool take_handler(server_t *server, client_t *client, char *line)
{
    size_t *index = NULL;
    char *item = get_resource_name(line);

    if (item == NULL)
        return false;
    index = malloc(sizeof(size_t));
    if (index == NULL) {
        perror("malloc failed");
        return false;
    }
    for (size_t i = 0; i < RESOURCES_TYPES_QUANTITY; i++) {
        if (strcmp(RESOURCES[i].name, item) == 0) {
            *index = i;
            setup_task(client->player->action_task, &take_callback, index);
            schedule_task(client->player->action_task, server, TAKE_DELAY, 1);
            return true;
        }
    }
    free(index);
    return false;
}
