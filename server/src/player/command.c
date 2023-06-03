/*
** EPITECH PROJECT, 2023
** server
** File description:
** player.c
*/

#include <string.h>

#include "constants.h"
#include "player.h"
#include "types.h"
#include "util.h"

void handle_player_command(server_t *server, client_t *client, char *line)
{
    char *command = strtok(line, " ");

    for (size_t i = 0; i < PLAYER_COMMANDS_COUNT; i++) {
        if (strcmp(command, PLAYER_COMMANDS[i].command) == 0) {
            PLAYER_COMMANDS[i].function(server, client, line);
            return;
        }
    }
    append_buffer(client->buffer, "%s%s", PLAYER_UNKNOWN, LINE_BREAK);
}
