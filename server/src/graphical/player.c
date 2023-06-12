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

static void send_inventory(client_t *client, player_t *player)
{
    for (size_t i = 0; i < RESOURCES_TYPES_QUANTITY; i++) {
        append_buffer(client->buffer_out, " %zu", player->inventory[i]);
    }
}

void pin_handler(server_t *server, client_t *client)
{
    char *line = strtok(NULL, " ");
    client_t *target = NULL;
    int id = 0;

    if (line == NULL || strtok(NULL, " ") != NULL || !check_number(line, &id)) {
        append_buffer(client->buffer_out, "%s%s",
            GRAPHICAL_COMMAND_PARAMETER, LINE_BREAK);
        return;
    }
    target = get_client_by_player_id(server, (size_t) id);
    if (target == NULL) {
        append_buffer(client->buffer_out, "%s%s", \
            GRAPHICAL_COMMAND_PARAMETER, LINE_BREAK);
        return;
    }
    append_buffer(client->buffer_out, "%s %zu %zu %zu", \
        GRAPHICAL_PLAYER_INVENTORY, target->player->id, \
        target->player->pos->x, target->player->pos->y);
    send_inventory(client, target->player);
    append_buffer(client->buffer_out, "%s", LINE_BREAK);
}

void plv_handler(server_t *server, client_t *client)
{
    char *line = strtok(NULL, " ");
    client_t *target = NULL;
    int id = 0;

    if (line == NULL || strtok(NULL, " ") != NULL || !check_number(line, &id)) {
        append_buffer(client->buffer_out, "%s%s",
            GRAPHICAL_COMMAND_PARAMETER, LINE_BREAK);
        return;
    }
    target = get_client_by_player_id(server, (size_t) id);
    if (target == NULL) {
        append_buffer(client->buffer_out, "%s%s", \
            GRAPHICAL_COMMAND_PARAMETER, LINE_BREAK);
        return;
    }
    append_buffer(client->buffer_out, "%s %zu %zu%s", GRAPHICAL_PLAYER_LEVEL, \
        target->player->id, target->player->level, LINE_BREAK);
}

void ppo_handler(server_t *server, client_t *client)
{
    char *line = strtok(NULL, " ");
    client_t *target = NULL;
    int id = 0;

    if (line == NULL || strtok(NULL, " ") != NULL || !check_number(line, &id)) {
        append_buffer(client->buffer_out, "%s%s",
            GRAPHICAL_COMMAND_PARAMETER, LINE_BREAK);
        return;
    }
    target = get_client_by_player_id(server, (size_t)id);
    if (target == NULL) {
        append_buffer(client->buffer_out, "%s%s", \
            GRAPHICAL_COMMAND_PARAMETER, LINE_BREAK);
        return;
    }
    append_buffer(client->buffer_out, "%s %zu %zu %zu %d%s", \
        GRAPHICAL_PLAYER_POSITION, target->player->id, target->player->pos->x,
        target->player->pos->y, target->player->direction + 1, LINE_BREAK);
}
