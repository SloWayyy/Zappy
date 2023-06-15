/*
** EPITECH PROJECT, 2023
** server
** File description:
** player.h
*/

#ifndef PLAYER_H_
    #define PLAYER_H_

    #define PLAYER_COMMANDS_COUNT \
        (sizeof(PLAYER_COMMANDS) / sizeof(player_command_t))
    #define INCANTATIONS_COUNT \
        (sizeof(INCANTATIONS) / sizeof(incantation_requirements_t))

    #include <stdbool.h>

    #include "constants.h"
    #include "resources.h"
    #include "types.h"

bool try_join_team(server_t *server, client_t *client, char *line);

void food_callback(server_t *server, client_t *client, void *arg);
void set_callback(server_t *server, client_t *client, void *arg);
void take_callback(server_t *server, client_t *client, void *arg);
void incantation_callback(server_t *server, client_t *client, void *arg);

bool forward_handler(server_t *server, client_t *client, char *line);
bool left_handler(server_t *server, client_t *client, char *line);
bool right_handler(server_t *server, client_t *client, char *line);
bool look_handler(server_t *server, client_t *client, char *line);
bool inventory_handler(server_t *server, client_t *client, char *line);
bool broadcast_handler(server_t *server, client_t *client, char *line);
bool slots_handler(server_t *server, client_t *client, char *line);
bool fork_handler(server_t *server, client_t *client, char *line);
bool eject_handler(server_t *server, client_t *client, char *line);
bool take_handler(server_t *server, client_t *client, char *line);
bool set_handler(server_t *server, client_t *client, char *line);
bool incantation_handler(server_t *server, client_t *client, char *line);

void register_command(server_t *server, client_t *client, char *line);
void flush_command(server_t *server, client_t *client);

typedef bool player_handler_t (server_t *server, client_t *client, char *line);

typedef struct player_command {
    char const *command;
    player_handler_t *function;
    bool args;
} player_command_t;

typedef struct incantation {
    player_list_t players;
    const incantation_requirements_t *requirements;
} incantation_t;

static const player_command_t PLAYER_COMMANDS[] = {
        { PLAYER_MOVE_FORWARD, &forward_handler, false },
        { PLAYER_MOVE_LEFT, &left_handler, false },
        { PLAYER_MOVE_RIGHT, &right_handler, false },
        { PLAYER_LOOK, &look_handler, false },
        { PLAYER_INVENTORY, &inventory_handler, false },
        { PLAYER_BROADCAST, &broadcast_handler, true },
        { PLAYER_UNUSED_SLOTS, &slots_handler, false },
        { PLAYER_FORK, &fork_handler, false },
        { PLAYER_EJECT, &eject_handler, false },
        { PLAYER_TAKE_OBJECT, &take_handler, true },
        { PLAYER_SET_OBJECT, &set_handler, true },
        { PLAYER_INCANTATION, &incantation_handler, false },
};

bool meet_requirements(incantation_t *incantation);
incantation_t *setup_incantation(player_t *player, \
    const incantation_requirements_t *requirements);
bool start_incantation(server_t *server, client_t *client, \
    incantation_t *incantation);

#endif
