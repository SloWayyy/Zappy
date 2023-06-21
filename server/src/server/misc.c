/*
** EPITECH PROJECT, 2023
** server
** File description:
** help.c
*/

#include "buffer.h"
#include "commands.h"
#include "constants.h"
#include "types.h"

void help_handler(server_t *server)
{
    char separator = '\0';

    append_buffer(server->data->stdout_buffer, "%s%s", \
        SERVER_HELP, LINE_BREAK);
    for (size_t i = 0; i < SERVER_COMMANDS_COUNT; i++) {
        separator = i % 5 == 4 || i == SERVER_COMMANDS_COUNT - 1 ? '\n' : ' ';
        append_buffer(server->data->stdout_buffer, "%s%c", \
            SERVER_COMMANDS[i].command, separator);
    }
}

void debug_handler_server(server_t *server)
{
    char *msg = NULL;

    server->options->debug = !server->options->debug;
    msg = server->options->debug ? SERVER_DEBUG_ENABLED : SERVER_DEBUG_DISABLED;
    append_buffer(server->data->stdout_buffer, "%s%s%s", \
        DEBUG_PREFIX, msg, LINE_BREAK);
}
