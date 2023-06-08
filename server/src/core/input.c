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

#include "constants.h"
#include "graphical.h"
#include "player.h"
#include "types.h"
#include "util.h"

static void handle_unknown(server_t *server, client_t *client, char *line)
{
    if (strcmp(line, GRAPHICAL_IDENTIFIER) == 0) {
        client->type = GRAPHIC;
        send_new_graphical(server, client);
    } else if (try_join_team(server, client, line)) {
        client->type = PLAYER;
        append_buffer(client->buffer_out, "%d%s%d %d%s", \
            client->player->team->slots, LINE_BREAK, \
            server->options->width, server->options->height, LINE_BREAK);
    } else {
        append_buffer(client->buffer_out, "%s%s", PLAYER_UNKNOWN, \
            LINE_BREAK);
    }
}

static void handle_client_input(server_t *server, client_t *client, char *line)
{
    if (client->type == PLAYER) {
        handle_player_command(server, client, line);
    } else if (client->type == GRAPHIC) {
        handle_graphical_command(server, client, line);
    } else {
        handle_unknown(server, client, line);
    }
}

static bool handle_input(server_t *server, client_t *client)
{
    bool exit = false;
    char buffer[BUFFER_EXTRA + 1];
    char *command = NULL;
    int re = read(client->fd, buffer, BUFFER_EXTRA);

    if (re <= 0) {
        return false;
    }
    buffer[re] = '\0';
    append_buffer(client->buffer_in, buffer);
    while (!exit) {
        command = extract_line(client->buffer_in);
        if (command != NULL) {
            handle_client_input(server, client, command);
            free(command);
        } else {
            exit = true;
        }
    }
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
    if (keep && FD_ISSET(client->fd, &server->data->writes)) {
        keep = dump_buffer(client->buffer_out, client->fd) && !dead;
    }
    return keep;
}
