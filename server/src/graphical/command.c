/*
** EPITECH PROJECT, 2023
** server
** File description:
** command.c
*/

#include <string.h>

#include "constants.h"
#include "graphical.h"
#include "types.h"
#include "util.h"

void handle_graphical_command(server_t *server, client_t *client, char *line)
{
    char *command = strtok(line, " ");

    for (size_t i = 0; i < GRAPHICAL_COMMANDS_COUNT; i++) {
        if (strcmp(command, GRAPHICAL_COMMANDS[i].command) == 0) {
            GRAPHICAL_COMMANDS[i].function(server, client);
            return;
        }
    }
    append_buffer(client->buffer, "%s%s", GRAPHICAL_UNKNOWN, LINE_BREAK);
}
