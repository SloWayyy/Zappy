/*
** EPITECH PROJECT, 2023
** server
** File description:
** info.c
*/

#include "constants.h"
#include "types.h"
#include "util.h"

void slots_handler(server_t *server, client_t *client)
{
    (void) server;
    append_buffer(client->buffer_out, "%d%s", client->player->team->slots, \
        LINE_BREAK);
}
