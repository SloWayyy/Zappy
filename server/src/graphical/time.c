/*
** EPITECH PROJECT, 2023
** server
** File description:
** time.c
*/

#include <string.h>
#include <sys/queue.h>

#include "buffer.h"
#include "constants.h"
#include "graphical.h"
#include "types.h"
#include "server.h"

void send_time(server_t *server, client_t *client)
{
    append_buffer(client->buffer_out, "%s %li%s", GRAPHICAL_FREQUENCY, \
        server->zappy->tick->freq, LINE_BREAK);
}

void sgt_handler(server_t *server, client_t *client)
{
    if (strtok(NULL, " ") != NULL) {
        append_buffer(client->buffer_out, "%s%s", \
            GRAPHICAL_COMMAND_PARAMETER, LINE_BREAK);
        return;
    }
    send_time(server, client);
}

static void send_time_update(server_t *server, client_t *client)
{
    client_t *node = NULL;

    SLIST_FOREACH(node, server->clients, next) {
        if (node->type == GRAPHIC && node != client) {
            append_buffer(node->buffer_out, "%s% li%s", GRAPHICAL_FREQUENCY, \
                server->zappy->tick->freq, LINE_BREAK);
        }
    }
}

void sst_handler(server_t *server, client_t *client)
{
    int ticks = 0;
    char *num = strtok(NULL, " ");

    if (num == NULL || strtok(NULL, " ") != NULL) {
        append_buffer(client->buffer_out, "%s%s", \
            GRAPHICAL_COMMAND_PARAMETER, LINE_BREAK);
        return;
    }
    if (!check_number(num, &ticks) || ticks < 1 || ticks > MAX_FREQ) {
        append_buffer(client->buffer_out, "%s%s", \
            GRAPHICAL_COMMAND_PARAMETER, LINE_BREAK);
        return;
    }
    init_tick(server, ticks);
    append_buffer(client->buffer_out, "%s %d%s", GRAPHICAL_CHANGE_FREQ, \
        ticks, LINE_BREAK);
    send_time_update(server, client);
}
