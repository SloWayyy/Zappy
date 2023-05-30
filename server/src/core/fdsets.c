/*
** EPITECH PROJECT, 2023
** MyFTP
** File description:
** fdsets.c
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/param.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/queue.h>
#include <unistd.h>

#include "server.h"
#include "types.h"
#include "util.h"

static bool handle_stdin(void)
{
    bool exit = false;
    size_t len = 0;
    char *line = NULL;

    if (getline(&line, &len, stdin) == -1) {
        exit = true;
    }
    free(line);
    return exit;
}

static void handle_incoming(server_t *server)
{
    int fd = accept(server->data->socket_fd, NULL, NULL);
    FILE *stream = NULL;
    client_t *client = NULL;

    if (fd == -1) {
        perror("accept failed");
        return;
    }
    stream = fdopen(fd, "r");
    client = new_client(fd, stream);
    if (stream == NULL || client == NULL) {
        close(fd);
        return;
    }
    append_buffer(client->buffer, "WELCOME\n");
    SLIST_INSERT_HEAD(server->clients, client, next);
}

static void handle_clients(server_t *server)
{
    bool keep = false;
    client_t *node = server->clients->slh_first;
    client_t *tmp = NULL;

    while (node != NULL) {
        tmp = node->next.sle_next;
        keep = true;
        if (FD_ISSET(node->fd, &server->data->reads)) {
            keep = handle_input(server, node);
        }
        if (keep && FD_ISSET(node->fd, &server->data->writes)) {
            keep = dump_buffer(node->buffer, node->fd);
        }
        if (!keep) {
            SLIST_REMOVE(server->clients, node, client, next);
            close_connection(node);
            free_connection(node);
        }
        node = tmp;
    }
}

int refresh_fdsets(server_t *server)
{
    int max_fd = server->data->socket_fd;
    client_t *node = NULL;

    FD_ZERO(&server->data->reads);
    FD_ZERO(&server->data->writes);
    FD_SET(STDIN_FILENO, &server->data->reads);
    FD_SET(server->data->socket_fd, &server->data->reads);
    FD_SET(server->data->signal_fd, &server->data->reads);
    SLIST_FOREACH(node, server->clients, next) {
        FD_SET(node->fd, &server->data->reads);
        if (node->buffer->size > 0) {
            FD_SET(node->fd, &server->data->writes);
        }
        max_fd = MAX(max_fd, node->fd);
    }
    return MAX(max_fd, server->data->signal_fd);
}

bool handle_fdsets(server_t *server)
{
    bool exit = false;

    if (FD_ISSET(STDIN_FILENO, &server->data->reads)) {
        exit = handle_stdin();
    }
    if (FD_ISSET(server->data->signal_fd, &server->data->reads)) {
        exit = true;
    }
    if (FD_ISSET(server->data->socket_fd, &server->data->reads)) {
        handle_incoming(server);
    }
    handle_clients(server);
    return exit;
}
