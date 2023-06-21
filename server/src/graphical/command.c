/*
** EPITECH PROJECT, 2023
** server
** File description:
** command.c
*/

#include <string.h>

#include "buffer.h"
#include "constants.h"
#include "graphical.h"
#include "types.h"

void handle_graphical_command(server_t *server, client_t *client, char *line)
{
    char *command = strtok(line, " ");

    for (size_t i = 0; i < GRAPHICAL_COMMANDS_COUNT; i++) {
        if (strcmp(command, GRAPHICAL_COMMANDS[i].command) == 0) {
            GRAPHICAL_COMMANDS[i].function(server, client);
            return;
        }
    }
    append_buffer(client->buffer_out, "%s%s", GRAPHICAL_UNKNOWN, LINE_BREAK);
}

void send_graphical_event(server_t *server, const char *format, ...)
{
    va_list list;
    va_list copy;
    client_t *node = NULL;

    va_start(list, format);
    SLIST_FOREACH(node, server->clients, next) {
        if (node->type == GRAPHIC) {
            va_copy(copy, list);
            vappend_buffer(node->buffer_out, format, copy);
            va_end(copy);
        }
    }
    va_end(list);
}
