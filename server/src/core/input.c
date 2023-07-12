/*
** EPITECH PROJECT, 2023
** server
** File description:
** input.c
*/

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <unistd.h>

#include "buffer.h"
#include "constants.h"
#include "server.h"
#include "types.h"

static void handle_commands(server_t *server, client_t *client)
{
    bool exit = false;
    char *command = NULL;

    while (!exit) {
        command = extract_line(client->buffer_in);
        if (command != NULL) {
            handle_client_input(server, client, command);
            free(command);
        } else {
            exit = true;
        }
    }
}

static bool handle_input(server_t *server, client_t *client)
{
    char buffer[BUFFER_EXTRA + 1];
    ssize_t re = 0;

    memset(buffer, 0, BUFFER_EXTRA + 1);
    re = read(client->fd, buffer, BUFFER_EXTRA);
    if (re <= 0) {
        return false;
    }
    buffer[re] = '\0';
    append_buffer(client->buffer_in, "%s", buffer);
    handle_commands(server, client);
    return true;
}

bool handle_client(server_t *server, client_t *client)
{
    bool keep = true;
    bool read = client->player == NULL || !client->player->dead;
    bool dead = client->player && client->player->dead;

    if (read && FD_ISSET(client->fd, &server->data->reads)) {
        keep = handle_input(server, client);
    }
    keep = keep && client->buffer_in->size < BUFFER_MAX;
    if (keep && FD_ISSET(client->fd, &server->data->writes)) {
        keep = dump_buffer(client->buffer_out, client->fd) && !dead;
    }
    return keep;
}
