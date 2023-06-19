/*
** EPITECH PROJECT, 2023
** server
** File description:
** start.c
*/

#include <stdbool.h>
#include <stdlib.h>
#include <sys/queue.h>

#include "buffer.h"
#include "constants.h"
#include "graphical.h"
#include "player.h"
#include "tasks.h"
#include "types.h"

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
    send_graphical_event(server, "%s %zu %zu %d%s", \
        GRAPHICAL_PLAYER_INCANTATION_END, client->player->pos->x, \
        client->player->pos->y, false, LINE_BREAK);
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

static void delay_incantation(server_t *server, incantation_t *incantation)
{
    player_t *node = NULL;
    client_t *target = NULL;

    SLIST_FOREACH(node, &incantation->players, next_incantation) {
        node->incantation = incantation;
        target = get_client_by_player_id(server, node->id);
        if (target != NULL) {
            append_buffer(target->buffer_out, "%s%s", \
            PLAYER_ELEVATION_START, LINE_BREAK);
            setup_task(target->player->action_task, NULL, NULL);
            schedule_task(target->player->action_task, server, \
            INCANTATION_DELAY, 1);
        }
    }
}

bool start_incantation(server_t *server, client_t *client, \
    incantation_t *incantation)
{
    if (!meet_requirements(incantation)) {
        start_error_incantation(server, client, incantation);
        return true;
    }
    if (!register_incantation(server, incantation)) {
        free(incantation);
        return false;
    }
    delay_incantation(server, incantation);
    return true;
}
