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

#include "buffer.h"
#include "commands.h"
#include "constants.h"
#include "objects.h"
#include "server.h"
#include "types.h"

static bool handle_stdin(server_t *server)
{
    size_t len = 0;
    ssize_t ret = 0;
    char *line = NULL;

    ret = getline(&line, &len, stdin);
    if (ret != -1) {
        append_buffer(server->data->stdin_buffer, line);
        execute_server_commands(server);
    }
    free(line);
    return ret == -1;
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
    append_buffer(client->buffer_out, "%s%s", WELCOME_MESSAGE, LINE_BREAK);
    SLIST_INSERT_HEAD(server->clients, client, next);
}

static void handle_clients(server_t *server)
{
    client_t *node = SLIST_FIRST(server->clients);
    client_t *tmp = NULL;

    while (node != NULL) {
        tmp = SLIST_NEXT(node, next);
        if (!handle_client(server, node)) {
            SLIST_REMOVE(server->clients, node, client, next);
            free_client(server, node);
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
    if (server->data->stdout_buffer->size > 0) {
        FD_SET(STDOUT_FILENO, &server->data->writes);
    }
    FD_SET(server->data->socket_fd, &server->data->reads);
    FD_SET(server->data->signal_fd, &server->data->reads);
    SLIST_FOREACH(node, server->clients, next) {
        FD_SET(node->fd, &server->data->reads);
        if (node->buffer_out->size > 0) {
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
        exit = handle_stdin(server);
    }
    if (FD_ISSET(STDOUT_FILENO, &server->data->writes)) {
        dump_buffer(server->data->stdout_buffer, STDOUT_FILENO);
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
