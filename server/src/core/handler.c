/*
** EPITECH PROJECT, 2023
** server
** File description:
** handler.c
*/

#include <stdbool.h>
#include <stdio.h>
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

static bool should_handle(server_t *server, client_t *client)
{
    if (!server->zappy->paused) {
        return true;
    }
    return client->type != PLAYER;
}

static bool handle_stdin(server_t *server)
{
    ssize_t ret = 0;
    char buffer[BUFFER_EXTRA + 1];

    ret = read(STDIN_FILENO, buffer, BUFFER_EXTRA);
    if (ret > 0) {
        buffer[ret] = '\0';
        append_buffer(server->data->stdin_buffer, buffer);
        execute_server_commands(server);
    }
    return ret <= 0;
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
    if (stream == NULL) {
        close(fd);
        return;
    }
    client = new_client(fd, stream);
    if (client == NULL) {
        fclose(stream);
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
        if (should_handle(server, node) && !handle_client(server, node)) {
            SLIST_REMOVE(server->clients, node, client, next);
            free_client(server, node);
        }
        node = tmp;
    }
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
