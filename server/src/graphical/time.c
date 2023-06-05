/*
** EPITECH PROJECT, 2023
** server
** File description:
** time.c
*/

#include <string.h>

#include "constants.h"
#include "graphical.h"
#include "types.h"
#include "util.h"

#include "server.h"

void sst_handler(server_t *server, client_t *client)
{
    int ticks = 0;
    char *num = strtok(NULL, " ");

    if (num == NULL || strtok(NULL, " ") != NULL) {
        append_buffer(client->buffer, "%s%s", \
            GRAPHICAL_COMMAND_PARAMETER, LINE_BREAK);
        return;
    }
    if (!check_number(num, &ticks) || ticks < 1 || ticks > MAX_FREQ) {
        append_buffer(client->buffer, "%s%s", \
            GRAPHICAL_COMMAND_PARAMETER, LINE_BREAK);
        return;
    }
    init_tick(server, ticks);
    append_buffer(client->buffer, "%s %d%s", GRAPHICAL_CHANGE_FREQ, \
        ticks, LINE_BREAK);
}

void sgt_handler(server_t *server, client_t *client)
{
    if (strtok(NULL, " ") != NULL) {
        append_buffer(client->buffer, "%s%s", \
            GRAPHICAL_COMMAND_PARAMETER, LINE_BREAK);
        return;
    }
    append_buffer(client->buffer, "%s %li%s", GRAPHICAL_FREQUENCY, \
        server->zappy->tick->freq, LINE_BREAK);
}
