/*
** EPITECH PROJECT, 2023
** server
** File description:
** scheduler.c
*/

#include <stdbool.h>
#include <stdio.h>
#include <sys/queue.h>

#include "tasks.h"
#include "types.h"

static void execute_task(server_t *server, task_t *task)
{
    task->current--;
    if (task->current > 0) {
        return;
    }
    task->current = task->delay;
    if (task->executions != -1) {
        task->executions--;
        if (task->executions == 0) {
            task->running = false;
        }
    }
    if (task->callback != NULL) {
        task->callback(server, task->client, task->arg);
    }
}

void execute_tasks(server_t *server)
{
    task_t *node = SLIST_FIRST(server->tasks);
    task_t *tmp = NULL;

    while (node != NULL) {
        tmp = SLIST_NEXT(node, next);
        if (node->running) {
            execute_task(server, node);
        }
        node = tmp;
    }
}
