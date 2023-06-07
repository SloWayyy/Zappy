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
    #include <stdbool.h>
    #include <stddef.h>
    #include <sys/queue.h>
    #include <sys/select.h>

typedef SLIST_HEAD(client_list, client) client_list_t;
typedef SLIST_HEAD(player_list, player) player_list_t;
typedef SLIST_HEAD(team_list, team) team_list_t;
typedef SLIST_HEAD(task_list, task) task_list_t;

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
    player_list_t *players;
    SLIST_ENTRY(team) next;
} team_t;

typedef struct tile {
    size_t x;
    size_t y;
    size_t resources[RESOURCES_TYPES_QUANTITY];
    player_list_t players;
} tile_t;

typedef struct player {
    size_t id;
    size_t level;
    size_t inventory[RESOURCES_TYPES_QUANTITY];
    team_t *team;
    tile_t *pos;
    direction_type_t direction;
    size_t action_task_id;
    bool dead;
    SLIST_ENTRY(player) next_team;
    SLIST_ENTRY(player) next_tile;
} player_t;

typedef struct client {
    int fd;
    FILE *stream;
    connection_type_t type;
    player_t *player;
    buffer_t *buffer_in;
    buffer_t *buffer_out;
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
    long freq;
    struct timeval tick_delay;
    struct timeval game_start;
    struct timeval last_tick;
} tick_t;

typedef struct zappy {
    tick_t *tick;
    tile_t **map;
    team_list_t *teams;
} zappy_t;

typedef struct server {
    options_t *options;
    data_t *data;
    zappy_t *zappy;
    client_list_t *clients;
    task_list_t *tasks;
} server_t;

typedef void (task_function_t)(server_t *server, client_t *client);

typedef struct task {
    size_t id;
    bool running;
    size_t delay;
    size_t current;
    int executions;
    client_t *client;
    task_function_t *callback;
    SLIST_ENTRY(task) next;
} task_t;

#endif
