/*
** EPITECH PROJECT, 2023
** server
** File description:
** command.c
*/

#include <stdio.h>

#include "types.h"

void handle_graphical_command(server_t *server, client_t *client, char *line)
{
    (void) server;
    (void) client;
    // TODO: Handle graphical command
    printf("Graphical command received: %s\n", line);
}
