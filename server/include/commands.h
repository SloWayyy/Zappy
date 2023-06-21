/*
** EPITECH PROJECT, 2023
** server
** File description:
** commands.h
*/

#ifndef COMMANDS_H_
    #define COMMANDS_H_

    #define SERVER_UNKNOWN "Unknown command. Type /help to get help."

    #define SERVER_MODIFIER_ALL_PLAYERS "@a"
    #define SERVER_MODIFIER_ALL_ENTITIES "@e"
    #define SERVER_MODIFIER_RANDOM "@r"

    #define SERVER_GIVE_LIMIT 1000

    #define SERVER_PLAYER_ERROR "Error: Cannot find player"
    #define SERVER_RESOURCE_ERROR "Error: Invalid resource type"

    #define SERVER_TP_PLAYER_USAGE "Usage: /tp <src> <dest>"
    #define SERVER_TP_COORD_USAGE "Usage: /tp <src> <x> <y>"
    #define SERVER_TP_ERROR "Error: Invalid destination"
    #define SERVER_TP_ENTITIES "Resources and eggs have been " \
        "teleported to (%zu %zu)%s"
    #define SERVER_TP_FORMAT "Player %zu has been teleported to (%zu %zu)%s"

    #define SERVER_GIVE_USAGE "Usage: /give <src> <resource> [amount]"
    #define SERVER_GIVE_ERROR "Error: You cannot give more " \
        "than %zu items at once%s"
    #define SERVER_GIVE_FORMAT "Player %zu has received %s x%zu%s"

    #define SERVER_KILL_USAGE "Usage: /kill <src>"
    #define SERVER_KILL_FORMAT "Player %zu has been killed%s"
    #define SERVER_KILL_ENTITIES "Resources and eggs have been killed"

    #define SERVER_COMMANDS_COUNT \
            (sizeof(SERVER_COMMANDS) / sizeof(server_command_t))

    #include <stdbool.h>

    #include "types.h"

void execute_server_commands(server_t *server);

void tp_handler(server_t *server);
void give_handler(server_t *server);
void kill_handler(server_t *server);

typedef void player_handler_t (server_t *server);

typedef struct server_command {
    char const *command;
    player_handler_t *function;
} server_command_t;

typedef struct source {
    player_t *player;
    bool all;
    bool entities;
} source_t;

static const server_command_t SERVER_COMMANDS[] = {
        { "/tp", &tp_handler },
        { "/give", &give_handler },
        { "/kill", &kill_handler },
};

bool get_source(server_t *server, char *target, source_t *ptr);
void teleport_players(server_t *server, source_t *source, tile_t *dest, \
    direction_type_t *ptr);

#endif
