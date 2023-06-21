/*
** EPITECH PROJECT, 2023
** server
** File description:
** client.c
*/

#include <criterion/criterion.h>
#include <pthread.h>
#include <unistd.h>

#include "tests.h"

static void wait_for_start(routine_t *routine)
{
    bool exit = false;

    while (!exit) {
        pthread_mutex_lock(routine->mutex);
        exit = routine->launch;
        pthread_mutex_unlock(routine->mutex);
    }
}

void exit_client(pthread_t *thread, routine_t *routine)
{
    int res = 0;
    char *ret = NULL;
    void *ptr = NULL;

    wait_for_start(routine);
    routine->type = EXIT;
    pthread_cond_signal(routine->cond);
    res = pthread_join(*thread, &ptr);
    ret = (char *) ptr;
    cr_assert_neq(res, -1, "Error: Could not exit client");
    cr_assert_null(ret, "%s", ret);
}

void execute_command(routine_t *routine, char *command)
{
    wait_for_start(routine);
    routine->type = COMMAND;
    routine->buffer = command;
    cr_assert_not_null(routine->buffer, "Error: malloc failed");
    pthread_cond_signal(routine->cond);
    usleep(50000);
}

void get_output(routine_t *routine)
{
    wait_for_start(routine);
    routine->type = OUTPUT;
    routine->buffer = NULL;
    pthread_cond_signal(routine->cond);
    usleep(50000);
}

routine_t *launch_client(pthread_t *thread, int port)
{
    routine_t *routine = malloc(sizeof(routine_t));
    pthread_mutex_t *mutex = malloc(sizeof(pthread_mutex_t));
    pthread_cond_t *cond = malloc(sizeof(pthread_cond_t));
    int res = 0;

    cr_assert_not_null(routine, "Error: malloc failed");
    cr_assert_not_null(mutex, "Error: malloc failed");
    cr_assert_not_null(cond, "Error: malloc failed");
    routine->launch = false;
    routine->port = port;
    routine->mutex = mutex;
    routine->cond = cond;
    cr_assert_neq(pthread_mutex_init(mutex, NULL), -1, "Error: Could not create client infos");
    cr_assert_neq(pthread_cond_init(cond, NULL), -1, "Error: Could not create client infos");
    res = pthread_create(thread, NULL, &client_routine, routine);
    cr_assert_neq(res, -1, "Error: Could not create client thread");
    wait_for_start(routine);
    return routine;
}
