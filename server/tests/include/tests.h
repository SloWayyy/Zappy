/*
** EPITECH PROJECT, 2023
** server
** File description:
** tests.h
*/

#ifndef TESTS_H_
    #define TESTS_H_

    #include <stdbool.h>
    #include <sys/types.h>

typedef enum routine_type {
    COMMAND,
    OUTPUT,
    EXIT
} routine_type_t;

typedef struct routine {
    bool launch;
    int port;
    char *buffer;
    routine_type_t type;
    pthread_mutex_t *mutex;
    pthread_cond_t *cond;
} routine_t;

typedef struct process {
    pid_t pid;
    int stdin_fd;
} process_t;

char *get_file_content(char *filepath);

routine_t *launch_client(pthread_t *thread, int port);
void execute_command(routine_t *routine, char *command);
void get_output(routine_t *routine);
void exit_client(pthread_t *thread, routine_t *routine);

void *client_routine(void *arg);

process_t *launch_server(char **argv);
void execute_server_command(process_t *process, char *command);
void exit_server(process_t *process);

#endif
