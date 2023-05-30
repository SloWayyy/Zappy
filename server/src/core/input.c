/*
** EPITECH PROJECT, 2023
** server
** File description:
** input.c
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "types.h"

bool handle_input(server_t *server, client_t *client)
{
    (void) server;
    char *line = NULL;
    size_t len = 0;
    ssize_t res = getline(&line, &len, client->stream);

    free(line);
    if (res == -1) {
        return false;
    }
    return true;
}
