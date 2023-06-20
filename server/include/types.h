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
    #include <stdbool.h>
    #include <stddef.h>
    #include <sys/queue.h>
    #include <sys/select.h>

    #include "resources.h"

typedef SLIST_HEAD(client_list, client) client_list_t;
typedef SLIST_HEAD(egg_list, egg) egg_list_t;
typedef SLIST_HEAD(player_list, player) player_list_t;
typedef SLIST_HEAD(task_list, task) task_list_t;
typedef SLIST_HEAD(team_list, team) team_list_t;
typedef STAILQ_HEAD(command_queue, command) command_queue_t;

struct buffer;
struct incantation;
struct server;
struct task;

typedef enum connection_type {
    UNKNOWN,
    GRAPHIC,
    PLAYER,
} connection_type_t;

typedef enum direction_type {
    NORTH,
    EAST,
    SOUTH,
    WEST,
} direction_type_t;

typedef struct options {
    int port;
    int width;
    int height;
    char const **names;
    int clients;
    int freq;
    bool debug;
    bool immortal;
} options_t;

typedef struct tile {
    size_t x;
    size_t y;
    size_t resources[RESOURCES_TYPES_QUANTITY];
    player_list_t players;
    egg_list_t eggs;
} tile_t;

typedef struct team {
    const char *name;
    size_t slots;
    player_list_t *players;
    egg_list_t *eggs;
    SLIST_ENTRY(team) next;
} team_t;

typedef struct command {
    char *command;
    STAILQ_ENTRY(command) next;
} command_t;

typedef struct egg {
    size_t id;
    bool immortal;
    size_t player_id;
    team_t *team;
    tile_t *pos;
    SLIST_ENTRY(egg) next_team;
    SLIST_ENTRY(egg) next_tile;
} egg_t;

typedef struct player {
    size_t id;
    bool dead;
    bool from_egg;
    size_t level;
    size_t inventory[RESOURCES_TYPES_QUANTITY];
    team_t *team;
    tile_t *pos;
    direction_type_t direction;
    struct task *action_task;
    command_queue_t *commands;
    struct incantation *incantation;
    SLIST_ENTRY(player) next_team;
    SLIST_ENTRY(player) next_tile;
    SLIST_ENTRY(player) next_incantation;
} player_t;

typedef struct client {
    int fd;
    FILE *stream;
    connection_type_t type;
    player_t *player;
    struct buffer *buffer_in;
    struct buffer *buffer_out;
    SLIST_ENTRY(client) next;
} client_t;

typedef struct data {
    int socket_fd;
    int signal_fd;
    fd_set reads;
    fd_set writes;
    struct timeval timeout;
    struct buffer *stdin_buffer;
    struct buffer *stdout_buffer;
} data_t;

typedef struct tick {
    size_t tick_nb;
    long freq;
    struct timeval tick_delay;
    struct timeval game_start;
    struct timeval last_tick;
} tick_t;

typedef struct zappy {
    tick_t *tick;
    tile_t **map;
    size_t total[RESOURCES_TYPES_QUANTITY];
    size_t current[RESOURCES_TYPES_QUANTITY];
    double *densities;
    tile_t **empty;
    tile_t **updated;
    team_list_t *teams;
} zappy_t;

typedef struct server {
    options_t *options;
    data_t *data;
    zappy_t *zappy;
    client_list_t *clients;
    task_list_t *tasks;
} server_t;

#endif
