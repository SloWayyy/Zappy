/*
** EPITECH PROJECT, 2023
** server
** File description:
** help.c
*/

#include <stdbool.h>
#include <stddef.h>

#include "buffer.h"
#include "commands.h"
#include "constants.h"
#include "graphical.h"
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

void pause_handler(server_t *server)
{
    if (server->zappy->paused) {
        append_buffer(server->data->stdout_buffer, "%s%s", \
            SERVER_PAUSE_ERROR, LINE_BREAK);
        return;
    }
    server->zappy->paused = true;
    send_graphical_event(server, "%s %s %d%s", \
        GRAPHICAL_CUSTOM, GRAPHICAL_CUSTOM_PAUSE, true, LINE_BREAK);
    append_buffer(server->data->stdout_buffer, "%s%s", \
        SERVER_PAUSE, LINE_BREAK);
}

void resume_handler(server_t *server)
{
    if (!server->zappy->paused) {
        append_buffer(server->data->stdout_buffer, "%s%s", \
            SERVER_RESUME_ERROR, LINE_BREAK);
        return;
    }
    server->zappy->paused = false;
    send_graphical_event(server, "%s %s %d%s", \
        GRAPHICAL_CUSTOM, GRAPHICAL_CUSTOM_PAUSE, false, LINE_BREAK);
    append_buffer(server->data->stdout_buffer, "%s%s", \
        SERVER_RESUME, LINE_BREAK);
}
