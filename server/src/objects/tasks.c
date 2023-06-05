/*
** EPITECH PROJECT, 2023
** server
** File description:
** tasks.c
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/queue.h>

#include "types.h"

static task_t *get_task_by_id(server_t *server, size_t id)
{
    task_t *node = NULL;

    SLIST_FOREACH(node, server->tasks, next) {
        if (node->id == id) {
            return node;
        }
    }
    return NULL;
}

size_t register_task(server_t *server, client_t *client, \
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
    SLIST_INSERT_HEAD(server->tasks, task, next);
    return task->id;
}

void schedule_task(server_t *server, size_t task_id, size_t delay, int exec)
{
    task_t *task = get_task_by_id(server, task_id);

    if (task == NULL) {
        return;
    }
    if (task->running) {
        return;
    }
    task->current = delay;
    task->delay = delay;
    task->executions = exec;
    task->running = true;
}

void cancel_task(server_t *server, size_t id)
{
    task_t *node = NULL;

    SLIST_FOREACH(node, server->tasks, next) {
        if (node->id == id) {
            node->running = false;
            return;
        }
    }
}

void cancel_client_tasks(server_t *server, client_t *client)
{
    task_t *node = server->tasks->slh_first;
    task_t *tmp = NULL;

    while (node != NULL) {
        tmp = node->next.sle_next;
        if (node->client == client) {
            SLIST_REMOVE(server->tasks, node, task, next);
            free(node);
        }
        node = tmp;
    }
}
