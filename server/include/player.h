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

    #define FOOD_CONSUME_TICKS 12
    #define FOOD_DEFAULT 10

    #define FORWARD_DELAY 7

    #define PLAYER_MOVE_FORWARD "Forward"
    #define PLAYER_UNUSED_SLOTS "Connect_nbr"

    #define PLAYER_OK "ok"
    #define PLAYER_KO "ko"
    #define PLAYER_DEATH "dead"
    #define PLAYER_UNKNOWN PLAYER_KO

    #include <stdbool.h>

    #include "types.h"

bool try_join_team(server_t *server, client_t *client, char *line);
void handle_player_command(server_t *server, client_t *client, char *line);

void food_callback(server_t *server, client_t *client);
void forward_callback(server_t *server, client_t *client);

void forward_handler(server_t *server, client_t *client, char *line);
void slots_handler(server_t *server, client_t *client, char *line);

typedef void (player_handler_t) \
    (server_t *server, client_t *client, char *line);

typedef struct player_command {
    char const *command;
    player_handler_t *function;
    bool args;
} player_command_t;

static const player_command_t PLAYER_COMMANDS[] = {
        { PLAYER_MOVE_FORWARD, &forward_handler, false },
        { PLAYER_UNUSED_SLOTS, &slots_handler, false },
};

#endif
