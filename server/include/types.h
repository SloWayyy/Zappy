/*
** EPITECH PROJECT, 2023
** server
** File description:
** types.h
*/

#ifndef TYPES_H_
    #define TYPES_H_

    #include <bits/types/FILE.h>
    #include <bits/types/struct_timeval.h>
    #include <stddef.h>
    #include <sys/queue.h>
    #include <sys/select.h>

typedef enum connection_type {
    UNKNOWN,
    GRAPHIC,
    PLAYER,
} connection_type_t;

typedef struct options {
    int port;
    int width;
    int height;
    char **names;
    int clients;
    int freq;
} options_t;

typedef struct buffer {
    char *buffer;
    size_t size;
    size_t capacity;
} buffer_t;

typedef struct client {
    int fd;
    FILE *stream;
    connection_type_t type;
    buffer_t *buffer;
    SLIST_ENTRY(client) next;
} client_t;

typedef struct data {
    int socket_fd;
    int signal_fd;
    fd_set reads;
    fd_set writes;
    struct timeval timeout;
} data_t;

typedef struct tick {
    size_t tick_nb;
    struct timeval tick_delay;
    struct timeval game_start;
    struct timeval last_tick;
} tick_t;

typedef struct zappy {
    tick_t *tick;
} zappy_t;

typedef struct server {
    options_t *options;
    data_t *data;
    zappy_t *zappy;
    SLIST_HEAD(client_list, client) *clients;
} server_t;

#endif
