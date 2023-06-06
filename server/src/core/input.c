/*
** EPITECH PROJECT, 2023
** server
** File description:
** input.c
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>

#include "constants.h"
#include "graphical.h"
#include "player.h"
#include "types.h"
#include "util.h"

static void send_new_player(server_t *server, client_t *client)
{
    static const char *format = "%d%s%d %d%s";
    team_t *team = client->player->team;

    append_buffer(client->buffer, format, team->slots, LINE_BREAK,
        server->options->width, server->options->height, LINE_BREAK);
}

static void handle_unknown(server_t *server, client_t *client, char *line)
{
    if (strcmp(line, GRAPHICAL_IDENTIFIER) == 0) {
        client->type = GRAPHIC;
    } else if (try_join_team(server, client, line)) {
        client->type = PLAYER;
        send_new_player(server, client);
    } else {
        append_buffer(client->buffer, "%s%s", PLAYER_UNKNOWN, \
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
    char *line = NULL;
    size_t len = 0;
    ssize_t res = getline(&line, &len, client->stream);

    if (res == -1) {
        free(line);
        return false;
    }
    if (res == 1) {
        return true;
    }
    printf("Received line %s\n", line);
    line[res - 1] = '\0';
    handle_client_input(server, client, line);
    free(line);
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
        keep = dump_buffer(client->buffer, client->fd) && !dead;
    }
    return keep;
}
