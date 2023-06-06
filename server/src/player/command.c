/*
** EPITECH PROJECT, 2023
** server
** File description:
** player.c
*/

#include <stdbool.h>
#include <string.h>

#include "constants.h"
#include "player.h"
#include "types.h"
#include "util.h"

void handle_player_command(server_t *server, client_t *client, char *line)
{
    bool accept = false;

    for (size_t i = 0; i < PLAYER_COMMANDS_COUNT; i++) {
        if (PLAYER_COMMANDS[i].args) {
            accept = strncmp(line, PLAYER_COMMANDS[i].command, \
                strlen(PLAYER_COMMANDS[i].command)) == 0;
        } else {
            accept = strcmp(line, PLAYER_COMMANDS[i].command) == 0;
        }
        if (accept) {
            PLAYER_COMMANDS[i].function(server, client, line);
            return;
        }
    }
    append_buffer(client->buffer, "%s%s", PLAYER_UNKNOWN, LINE_BREAK);
}
