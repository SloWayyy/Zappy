/*
** EPITECH PROJECT, 2023
** server
** File description:
** clients.c
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/queue.h>

#include "buffer.h"
#include "constants.h"
#include "graphical.h"
#include "objects.h"
#include "tasks.h"
#include "types.h"

static bool init_buffers(client_t *client)
{
    client->buffer_in = new_buffer();
    if (client->buffer_in == NULL) {
        perror("malloc failed");
        return false;
    }
    client->buffer_out = new_buffer();
    if (client->buffer_out == NULL) {
        free_buffer(client->buffer_in);
        perror("malloc failed");
        return false;
    }
    return true;
}

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
    if (!init_buffers(new)) {
        free(new);
        return NULL;
    }
    return new;
}

void free_client(server_t *server, client_t *client)
{
    fclose(client->stream);
    if (client->player != NULL) {
        send_graphical_event(server, "%s %zu%s", \
            GRAPHICAL_PLAYER_DEATH, client->player->id, LINE_BREAK);
        free_player(client->player);
    }
    cancel_client_tasks(server, client);
    free_buffer(client->buffer_in);
    free_buffer(client->buffer_out);
    free(client);
}

void free_clients(server_t *server)
{
    client_t *node = NULL;

    while (!SLIST_EMPTY(server->clients)) {
        node = SLIST_FIRST(server->clients);
        SLIST_REMOVE_HEAD(server->clients, next);
        free_client(server, node);
    }
}

client_t *get_client_by_player_id(server_t *server, size_t id)
{
    client_t *node = NULL;

    SLIST_FOREACH(node, server->clients, next) {
        if (node->player != NULL && node->player->id == id) {
            return node;
        }
    }
    return NULL;
}
