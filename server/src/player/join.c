/*
** EPITECH PROJECT, 2023
** server
** File description:
** team_join.c
*/

#include <stdbool.h>
#include <string.h>
#include <sys/queue.h>

#include "types.h"

static bool check_capacity(server_t *server, client_t *client, team_t *team)
{
    (void) server;
    (void) client;
    (void) team;
    // TODO: Check capacity
    return true;
}

bool try_join_team(server_t *server, client_t *client, char *line)
{
    team_t *node = NULL;

    SLIST_FOREACH(node, server->zappy->teams, next) {
        if (strcmp(line, node->name) == 0) {
            return check_capacity(server, client, node);
        }
    }
    return false;
}
