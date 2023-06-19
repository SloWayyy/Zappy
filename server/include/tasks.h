/*
** EPITECH PROJECT, 2023
** server
** File description:
** tasks.h
*/

#ifndef TASKS_H_
    #define TASKS_H_

    #include <stdbool.h>
    #include <stddef.h>
    #include <sys/queue.h>

struct client;
struct server;

typedef void task_function_t \
    (struct server *server, struct client *client, void *arg);

typedef struct task {
    size_t id;
    bool running;
    size_t delay;
    size_t current;
    int executions;
    struct client *client;
    void *arg;
    task_function_t *callback;
    SLIST_ENTRY(task) next;
} task_t;

task_t *register_task(struct server *server, struct client *client, \
    task_function_t *callback);
void setup_task(task_t *task, task_function_t *callback, void *arg);
void schedule_task(task_t *task, struct server *server, size_t delay, int exec);
void cancel_client_tasks(struct server *server, struct client *client);
void execute_tasks(struct server *server);

#endif
