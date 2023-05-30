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

void handle_incoming(server_t *server)
{
    int fd = accept(server->socket_fd, NULL, NULL);
    FILE *stream = NULL;
    client_t *client = NULL;

    if (fd == -1) {
        perror("accept failed");
        return;
    }
    stream = fdopen(fd, "r");
    if (stream == NULL) {
        close(fd);
        return;
    }
    client = new_client(fd, stream);
    SLIST_INSERT_HEAD(server->clients, client, next);
}

void handle_clients(server_t *server, fd_set *set)
{
    client_t *node = server->clients->slh_first;
    client_t *tmp = NULL;

    while (node != NULL) {
        tmp = node->next.sle_next;
        if (FD_ISSET(node->fd, set)) {
            // TODO: handle_client(server, node);
        }
        node = tmp;
    }
}

bool handle_stdin(void)
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

int refresh_fdsets(server_t *server, fd_set *set)
{
    int max_fd = server->socket_fd;
    client_t *node = NULL;

    FD_ZERO(set);
    FD_SET(0, set);
    FD_SET(server->socket_fd, set);
    FD_SET(server->signal_fd, set);
    SLIST_FOREACH(node, server->clients, next) {
        FD_SET(node->fd, set);
        max_fd = MAX(max_fd, node->fd);
    }
    return MAX(max_fd, server->signal_fd);
}

bool handle_fdsets(server_t *server, fd_set *set)
{
    bool exit = false;

    if (FD_ISSET(0, set)) {
        exit = handle_stdin();
    }
    if (FD_ISSET(server->signal_fd, set)) {
        exit = true;
    }
    if (FD_ISSET(server->socket_fd, set)) {
        handle_incoming(server);
    }
    handle_clients(server, set);
    return exit;
}
