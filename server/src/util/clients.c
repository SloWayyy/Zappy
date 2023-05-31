/*
** EPITECH PROJECT, 2023
** server
** File description:
** clients.c
*/

#include <stdio.h>
#include <stdlib.h>

#include "server.h"
#include "types.h"
#include "util.h"

client_t *new_client(int fd, FILE *stream)
{
    client_t *new = malloc(sizeof(client_t));

    if (new == NULL) {
        perror("malloc failed");
        return NULL;
    }
    new->fd = fd;
    new->stream = stream;
    new->type = UNKNOWN;
    new->buffer = new_buffer();
    if (new->buffer == NULL) {
        perror("malloc failed");
        free(new);
        return NULL;
    }
    return new;
}

void close_connection(client_t *client)
{
    fclose(client->stream);
}

void free_connection(client_t *client)
{
    free_buffer(client->buffer);
    free(client);
}
