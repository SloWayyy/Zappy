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

    #define FOOD_CONSUME_TICKS 126
    #define FOOD_DEFAULT 10
    #define MAX_ACTIONS 10

    #define FORWARD_DELAY 7
    #define LEFT_DELAY 7
    #define RIGHT_DELAY 7
    #define LOOK_DELAY 7
    #define INVENTORY_DELAY 1
    #define BROADCAST_DELAY 7
    #define SLOTS_DELAY 0
    #define FORK_DELAY 42
    #define EJECT_DELAY 7
    #define TAKE_DELAY 7
    #define SET_DELAY 7
    #define INCANTATION_DELAY 300

    #define PLAYER_MOVE_FORWARD "Forward"
    #define PLAYER_MOVE_LEFT "Left"
    #define PLAYER_MOVE_RIGHT "Right"
    #define PLAYER_LOOK "Look"
    #define PLAYER_INVENTORY "Inventory"
    #define PLAYER_BROADCAST "Broadcast"
    #define PLAYER_FORK "Fork"
    #define PLAYER_EJECT "Eject"
    #define PLAYER_UNUSED_SLOTS "Connect_nbr"
    #define PLAYER_TAKE_OBJECT "Take"
    #define PLAYER_SET_OBJECT "Set"
    #define PLAYER_INCANTATION "Incantation"

    #define PLAYER_OK "ok"
    #define PLAYER_KO "ko"
    #define PLAYER_EJECTION "eject:"
    #define PLAYER_MESSAGE "message"
    #define PLAYER_ELEVATION_START "Elevation underway"
    #define PLAYER_ELEVATION_END "Current level:"
    #define PLAYER_DEATH "dead"
    #define PLAYER_UNKNOWN PLAYER_KO

    #include <stdbool.h>

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

typedef bool (player_handler_t) \
    (server_t *server, client_t *client, char *line);

typedef struct player_command {
    char const *command;
    player_handler_t *function;
    bool args;
} player_command_t;

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

static const incantation_requirements_t INCANTATIONS[] = {
    { 1, 1, { 0, 1, 0, 0, 0, 0, 0 } },
    { 2, 2, { 0, 1, 1, 1, 0, 0, 0 } },
    { 3, 2, { 0, 2, 0, 1, 0, 2, 0 } },
    { 4, 4, { 0, 1, 1, 2, 0, 1, 0 } },
    { 5, 4, { 0, 1, 2, 1, 3, 0, 0 } },
    { 6, 6, { 0, 1, 2, 3, 0, 1, 0 } },
    { 7, 6, { 0, 2, 2, 2, 2, 2, 1 } },
};

bool meet_requirements(incantation_t *incantation);
incantation_t *setup_incantation(player_t *player, \
    const incantation_requirements_t *requirements);
bool start_incantation(server_t *server, client_t *client, \
    incantation_t *incantation);

#endif
