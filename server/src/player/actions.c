/*
** EPITECH PROJECT, 2023
** server
** File description:
** actions.c
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/queue.h>

#include "constants.h"
#include "player.h"
#include "server.h"
#include "types.h"
#include "util.h"

static bool can_accept_task(client_t *client)
{
    size_t len = 0;
    action_t *action = NULL;

    if (!client->player->action_task->running) {
        return true;
    }
    STAILQ_FOREACH(action, client->player->actions, next) {
        len++;
    }
    return len < MAX_ACTIONS - 1;
}

void schedule_action(client_t *client, task_function_t *callback, \
    size_t delay, void *arg)
{
    action_t *action = NULL;

    if (!can_accept_task(client)) {
        append_buffer(client->buffer_out, "%s%s", PLAYER_KO, LINE_BREAK);
        return;
    }
    if (!client->player->action_task->running) {
        client->player->action_task->callback = callback;
        schedule_task(client->player->action_task, delay, 1, arg);
        return;
    }
    action = malloc(sizeof(action_t));
    if (action == NULL) {
        perror("malloc failed");
        return;
    }
    action->callback = callback;
    action->delay = delay;
    action->arg = arg;
    STAILQ_INSERT_TAIL(client->player->actions, action, next);
}

void flush_action(player_t *player)
{
    action_t *action = STAILQ_FIRST(player->actions);

    if (action == NULL) {
        return;
    }
    STAILQ_REMOVE_HEAD(player->actions, next);
    player->action_task->callback = action->callback;
    schedule_task(player->action_task, action->delay, 1, action->arg);
    free(action);
}
