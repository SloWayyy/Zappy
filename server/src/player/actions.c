/*
** EPITECH PROJECT, 2023
** server
** File description:
** actions.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/queue.h>

#include "server.h"
#include "types.h"

void schedule_action(player_t *player, task_function_t *callback, \
    size_t delay, void *arg)
{
    action_t *action = NULL;

    if (!player->action_task->running) {
        player->action_task->callback = callback;
        schedule_task(player->action_task, delay, 1, arg);
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
    STAILQ_INSERT_TAIL(player->actions, action, next);
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
