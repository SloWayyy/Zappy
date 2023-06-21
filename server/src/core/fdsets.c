/*
** EPITECH PROJECT, 2023
** MyFTP
** File description:
** fdsets.c
*/

#include <sys/param.h>
#include <unistd.h>

#include "buffer.h"
#include "types.h"

static int refresh_client_fdset(server_t *server, client_t *client)
{
    if (server->zappy->paused && client->type == PLAYER) {
        return -1;
    }
    FD_SET(client->fd, &server->data->reads);
    if (client->buffer_out->size > 0) {
        FD_SET(client->fd, &server->data->writes);
    }
    return client->fd;
}

int refresh_fdsets(server_t *server)
{
    int max_fd = server->data->socket_fd;
    client_t *node = NULL;

    FD_ZERO(&server->data->reads);
    FD_ZERO(&server->data->writes);
    FD_SET(STDIN_FILENO, &server->data->reads);
    if (server->data->stdout_buffer->size > 0) {
        FD_SET(STDOUT_FILENO, &server->data->writes);
    }
    FD_SET(server->data->socket_fd, &server->data->reads);
    FD_SET(server->data->signal_fd, &server->data->reads);
    SLIST_FOREACH(node, server->clients, next) {
        max_fd = MAX(max_fd, refresh_client_fdset(server, node));
    }
    return MAX(max_fd, server->data->signal_fd);
}
