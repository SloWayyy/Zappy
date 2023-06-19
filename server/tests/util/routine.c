/*
** EPITECH PROJECT, 2023
** server
** File description:
** routine.c
*/

#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "constants.h"
#include "tests.h"

static bool connect_client(int socket_fd, int port)
{
    int ret = -1;

    struct sockaddr_in addr = {
            .sin_family = AF_INET,
            .sin_port = htons(port),
            .sin_addr = { inet_addr("127.0.0.1") },
    };
    struct sockaddr *addr_ptr = (struct sockaddr *)&addr;

    for (int i = 0; i < 5 && ret == -1; i++) {
        ret = connect(socket_fd, addr_ptr, sizeof(addr));
        usleep(1000000);
    }
    return ret != -1;
}

static void dump_client_buffer(routine_t *routine, int socket_fd)
{
    bool exit = false;
    int res = 0;
    size_t size = 0;

    while (!exit) {
        routine->buffer = realloc(routine->buffer, size + 2048);
        if (routine->buffer == NULL) {
            return;
        }
        res = read(socket_fd, routine->buffer + size, 2048);
        if (res < BUFFER_SIZE) {
            exit = true;
            routine->buffer[size + res] = '\0';
        }
        size += 2048;
    }
    routine->buffer = routine->buffer;
}

static void client_loop(routine_t *routine, int socket_fd)
{
    bool exit = false;

    routine->launch = true;
    while (!exit) {
        pthread_mutex_lock(routine->mutex);
        pthread_cond_wait(routine->cond, routine->mutex);
        routine->launch = false;
        if (routine->type == COMMAND) {
            write(socket_fd, routine->buffer, strlen(routine->buffer));
            write(socket_fd, "\n", 1);
            routine->buffer = NULL;
        } else if (routine->type == OUTPUT) {
            dump_client_buffer(routine, socket_fd);
        } else if (routine->type == EXIT) {
            exit = true;
        }
        routine->launch = true;
        pthread_mutex_unlock(routine->mutex);
    }
    close(socket_fd);
}

void *client_routine(void *arg)
{
    routine_t *routine = (routine_t *) arg;

    int socket_fd = 0;

    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd == -1) {
        return "Error: Could not create socket";
    }
    if (!connect_client(socket_fd, routine->port)) {
        return "Error: Could not connect to server";
    }
    client_loop(routine, socket_fd);
    return NULL;
}
