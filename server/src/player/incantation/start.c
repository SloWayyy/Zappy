/*
** EPITECH PROJECT, 2023
** server
** File description:
** start.c
*/

#include <stdbool.h>
#include <stdlib.h>
#include <sys/queue.h>

#include "constants.h"
#include "player.h"
#include "server.h"
#include "types.h"
#include "util.h"

static bool register_incantation(server_t *server, incantation_t *incantation)
{
    task_t *task = register_task(server, NULL, &incantation_callback);

    if (task == NULL) {
        return false;
    }
    task->arg = incantation;
    schedule_task(task, server, INCANTATION_DELAY, 1);
    return true;
}

static void fail_incantation(server_t *server, client_t *client, \
    UNUSED void *arg)
{
    client->player->incantation = NULL;
    append_buffer(client->buffer_out, "%s%s", PLAYER_KO, LINE_BREAK);
    flush_command(server, client);
}

static void start_error_incantation(server_t *server, client_t *client, \
    incantation_t *incantation)
{
    client->player->incantation = incantation;
    append_buffer(client->buffer_out, "%s%s", PLAYER_KO, LINE_BREAK);
    setup_task(client->player->action_task, &fail_incantation, incantation);
    schedule_task(client->player->action_task, server, INCANTATION_DELAY, 1);
}

bool start_incantation(server_t *server, client_t *client, \
    incantation_t *incantation)
{
    player_t *node = NULL;

    if (meet_requirements(incantation)) {
        start_error_incantation(server, client, incantation);
        return true;
    }
    if (!register_incantation(server, incantation)) {
        free(incantation);
        return false;
    }
    SLIST_FOREACH(node, &incantation->players, next_incantation) {
        node->incantation = incantation;
        append_buffer(client->buffer_out, "%s%s", \
            PLAYER_ELEVATION_START, LINE_BREAK);
        setup_task(client->player->action_task, NULL, NULL);
        schedule_task(client->player->action_task, server, \
            INCANTATION_DELAY, 1);
    }
    return true;
}
