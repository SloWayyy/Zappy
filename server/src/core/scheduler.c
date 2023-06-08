/*
** EPITECH PROJECT, 2023
** server
** File description:
** scheduler.c
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "server.h"
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
    task->callback(server, task->client, task->arg);
}

void execute_tasks(server_t *server)
{
    task_t *node = server->tasks->slh_first;
    task_t *tmp = NULL;

    while (node != NULL) {
        tmp = node->next.sle_next;
        if (node->running) {
            execute_task(server, node);
        }
        node = tmp;
    }
}

task_t *register_task(server_t *server, client_t *client, \
    task_function_t *callback)
{
    static size_t next_id = 1;
    task_t *task = malloc(sizeof(task_t));

    if (task == NULL) {
        perror("malloc failed");
        return 0;
    }
    task->id = next_id++;
    task->running = false;
    task->current = 0;
    task->delay = 0;
    task->executions = 0;
    task->client = client;
    task->callback = callback;
    task->arg = NULL;
    SLIST_INSERT_HEAD(server->tasks, task, next);
    return task;
}

void schedule_task(task_t *task, size_t delay, int exec, void *arg)
{
    if (task->running) {
        return;
    }
    if (task->arg != NULL) {
        free(task->arg);
    }
    task->arg = arg;
    task->current = delay;
    task->delay = delay;
    task->executions = exec;
    task->running = true;
}

void cancel_client_tasks(server_t *server, client_t *client)
{
    task_t *node = server->tasks->slh_first;
    task_t *tmp = NULL;

    while (node != NULL) {
        tmp = node->next.sle_next;
        if (node->client == client) {
            SLIST_REMOVE(server->tasks, node, task, next);
            free(node->arg);
            free(node);
        }
        node = tmp;
    }
}
