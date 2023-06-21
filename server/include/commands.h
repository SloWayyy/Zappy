/*
** EPITECH PROJECT, 2023
** server
** File description:
** commands.h
*/

#ifndef COMMANDS_H_
    #define COMMANDS_H_

    #define SERVER_UNKNOWN "Unknown command. Type /help to get help."

    #define SERVER_MODIFIER_ALL "@a"
    #define SERVER_MODIFIER_RANDOM "@r"

    #define SERVER_PLAYER_ERROR "Error: Cannot find player"

    #define SERVER_TP_PLAYER_USAGE "Usage: /tp <src> <dest>"
    #define SERVER_TP_COORD_USAGE "Usage: /tp <src> <x> <y>"
    #define SERVER_TP_ERROR "Error: Invalid destination"
    #define SERVER_TP_FORMAT "Player %zu has been teleported to (%zu %zu)%s"

    #define SERVER_COMMANDS_COUNT \
            (sizeof(SERVER_COMMANDS) / sizeof(server_command_t))

    #include <stdbool.h>

    #include "types.h"

void execute_server_commands(server_t *server);
bool get_source(server_t *server, char *target, player_t **ptr);

void tp_handler(server_t *server);

typedef void player_handler_t (server_t *server);

typedef struct server_command {
    char const *command;
    player_handler_t *function;
} server_command_t;

static const server_command_t SERVER_COMMANDS[] = {
        { "/tp", &tp_handler },
};

#endif
