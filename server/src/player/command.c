/*
** EPITECH PROJECT, 2023
** server
** File description:
** player.c
*/

#include <stdio.h>

#include "types.h"

void handle_player_command(server_t *server, client_t *client, char *line)
{
    (void) server;
    (void) client;
    // TODO: Handle player command
    printf("Player command received: %s\n", line);
}
