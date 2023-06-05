/*
** EPITECH PROJECT, 2023
** server
** File description:
** team_name_answers.c
*/

#include <stddef.h>
#include <string.h>

#include "constants.h"
#include "graphical.h"
#include "server.h"
#include "types.h"
#include "util.h"

void pin_handler(server_t *server, client_t *client)
{
    char *line = strtok(NULL, " ");
    client_t *target = NULL;
    int id = 0;

    if (line == NULL || strtok(NULL, " ") != NULL || !check_number(line, &id)) {
        append_buffer(client->buffer, "%s%s",
        GRAPHICAL_COMMAND_PARAMETER, LINE_BREAK);
        return;
    }
    target = get_client_by_player_id(server, (size_t)id);
    if (target == NULL) {
        append_buffer(client->buffer, "%s\n", GRAPHICAL_COMMAND_PARAMETER);
        return;
    }
    append_buffer(client->buffer, "%s %zu %zu %zu %zu %zu %zu %zu %zu %zu%s", \
        GRAPHICAL_PLAYER_INVENTORY, target->player->id, target->player->pos->x,
        target->player->pos->y, target->player->inventory[0], \
        target->player->inventory[1], target->player->inventory[2], \
        target->player->inventory[3], target->player->inventory[4], \
        target->player->inventory[5], LINE_BREAK);
}

void plv_handler(server_t *server, client_t *client)
{
    char *line = strtok(NULL, " ");
    client_t *target = NULL;
    int id = 0;

    if (line == NULL || strtok(NULL, " ") != NULL || !check_number(line, &id)) {
        append_buffer(client->buffer, "%s%s",
        GRAPHICAL_COMMAND_PARAMETER, LINE_BREAK);
        return;
    }
    target = get_client_by_player_id(server, (size_t)id);
    if (target == NULL) {
        append_buffer(client->buffer, "%s\n", GRAPHICAL_COMMAND_PARAMETER);
        return;
    }
    append_buffer(client->buffer, "%s %zu %zu%s", GRAPHICAL_PLAYER_LEVEL, \
        target->player->id, target->player->level, LINE_BREAK);
}
