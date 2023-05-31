/*
** EPITECH PROJECT, 2023
** server
** File description:
** types.h
*/

#ifndef TYPES_H_
    #define TYPES_H_

    #define RESOURCES_TYPES_QUANTITY 7

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

typedef enum resource_type {
    FOOD,
    LINEMATE,
    DERAUMERE,
    SIBUR,
    MENDIANE,
    PHIRAS,
    THYSTAME,
} resource_type_t;

typedef struct options {
    int port;
    int width;
    int height;
    char const **names;
    int clients;
    int freq;
} options_t;

typedef struct buffer {
    char *buffer;
    size_t size;
    size_t capacity;
} buffer_t;

typedef struct team {
    const char *name;
    size_t capacity;
    size_t slots;
    SLIST_HEAD(player_list, player) *players;
    SLIST_ENTRY(team) next;
} team_t;

typedef struct player {
    team_t *team;
    size_t inventory[RESOURCES_TYPES_QUANTITY];
    size_t food_ticks;
} player_t;

typedef struct client {
    int fd;
    FILE *stream;
    connection_type_t type;
    player_t *player;
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
    SLIST_HEAD(teams_list, team) *teams;
} zappy_t;

typedef struct server {
    options_t *options;
    data_t *data;
    zappy_t *zappy;
    SLIST_HEAD(client_list, client) *clients;
} server_t;

#endif
