/*
** EPITECH PROJECT, 2023
** server
** File description:
** types.h
*/

#ifndef TYPES_H_
    #define TYPES_H_

    #include <bits/types/FILE.h>
    #include <sys/queue.h>

typedef struct options {
    int port;
    int width;
    int height;
    char **names;
    int clientsNb;
    int freq;
} options_t;

typedef struct client {
    int fd;
    FILE *stream;
    char *buffer;
    SLIST_ENTRY(client) next;
} client_t;

typedef struct server {
    int port;
    int socket_fd;
    int signal_fd;
    SLIST_HEAD(client_list, client) *clients;
} server_t;

#endif
