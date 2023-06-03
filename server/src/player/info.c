/*
** EPITECH PROJECT, 2023
** server
** File description:
** info.c
*/

#include "constants.h"
#include "types.h"
#include "util.h"

void slots_handler(server_t *server, client_t *client, char *line)
{
    (void) server;
    (void) line;
    append_buffer(client->buffer, "%d%s", client->player->team->slots, \
        LINE_BREAK);
}
