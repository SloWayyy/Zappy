/*
** EPITECH PROJECT, 2023
** server
** File description:
** clients.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/queue.h>

#include "objects.h"
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
    new->player = NULL;
    new->buffer = new_buffer();
    if (new->buffer == NULL) {
        perror("malloc failed");
        free(new);
        return NULL;
    }
    return new;
}

void close_client(client_t *client)
{
    fclose(client->stream);
}

void free_client(client_t *client)
{
    if (client->player != NULL) {
        free_player(client->player);
    }
    free_buffer(client->buffer);
    free(client);
}

void free_clients(server_t *server)
{
    client_t *node = NULL;

    while (!SLIST_EMPTY(server->clients)) {
        node = SLIST_FIRST(server->clients);
        SLIST_REMOVE_HEAD(server->clients, next);
        close_client(node);
        free_client(node);
    }
}
