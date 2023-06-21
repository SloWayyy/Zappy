/*
** EPITECH PROJECT, 2023
** server
** File description:
** commands.c
*/

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "buffer.h"
#include "commands.h"
#include "constants.h"
#include "types.h"

static void handle_server_command(server_t *server, char *line)
{
    char *command = strtok(line, " ");

    for (size_t i = 0; i < SERVER_COMMANDS_COUNT; i++) {
        if (strcmp(command, SERVER_COMMANDS[i].command) == 0) {
            SERVER_COMMANDS[i].function(server);
            return;
        }
    }
    append_buffer(server->data->stdout_buffer, "%s%s", \
        SERVER_UNKNOWN, LINE_BREAK);
}

void execute_server_commands(server_t *server)
{
    bool exit = false;
    char *command = NULL;

    while (!exit) {
        command = extract_line(server->data->stdin_buffer);
        if (command != NULL && command[0] == '/') {
            handle_server_command(server, command);
            free(command);
        } else {
            exit = true;
        }
    }
}
