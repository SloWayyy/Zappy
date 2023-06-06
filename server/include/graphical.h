/*
** EPITECH PROJECT, 2023
** server
** File description:
** graphical.h
*/

#ifndef GRAPHICAL_H_
    #define GRAPHICAL_H_

    #define GRAPHICAL_COMMANDS_COUNT \
        (sizeof(GRAPHICAL_COMMANDS) / sizeof(graphical_command_t))

    #define GRAPHICAL_IDENTIFIER "GRAPHIC"

    #define GRAPHICAL_MAP_SIZE "msz"
    #define GRAPHICAL_TILE_CONTENT "bct"
    #define GRAPHICAL_ALL_TILE_CONTENT "mct"
    #define GRAPHICAL_TEAMS_NAMES "tna"
    #define GRAPHICAL_PLAYER_POSITION "ppo"
    #define GRAPHICAL_PLAYER_LEVEL "plv"
    #define GRAPHICAL_PLAYER_INVENTORY "pin"
    #define GRAPHICAL_FREQUENCY "sgt"
    #define GRAPHICAL_CHANGE_FREQ "sst"

    #define GRAPHICAL_PLAYER_DEATH "pdi"

    #define GRAPHICAL_UNKNOWN "suc"
    #define GRAPHICAL_COMMAND_PARAMETER "sbp"

    #include "types.h"

void handle_graphical_command(server_t *server, client_t *client, char *line);
void send_graphical_event(server_t *server, const char *format, ...);
client_t *get_client_by_player_id(server_t *server, size_t id);

void msz_handler(server_t *server, client_t *client);
void bct_handler(server_t *server, client_t *client);
void mct_handler(server_t *server, client_t *client);
void tna_handler(server_t *server, client_t *client);
void ppo_handler(server_t *server, client_t *client);
void plv_handler(server_t *server, client_t *client);
void pin_handler(server_t *server, client_t *client);
void sgt_handler(server_t *server, client_t *client);
void sst_handler(server_t *server, client_t *client);

typedef void (graphical_handler_t) (server_t *server, client_t *client);

typedef struct graphical_command {
    char const *command;
    graphical_handler_t *function;
} graphical_command_t;

static const graphical_command_t GRAPHICAL_COMMANDS[] = {
        { GRAPHICAL_MAP_SIZE, &msz_handler },
        { GRAPHICAL_TILE_CONTENT, &bct_handler },
        { GRAPHICAL_ALL_TILE_CONTENT, &mct_handler },
        { GRAPHICAL_TEAMS_NAMES, &tna_handler },
        { GRAPHICAL_PLAYER_INVENTORY, &pin_handler },
        { GRAPHICAL_PLAYER_POSITION, &ppo_handler },
        { GRAPHICAL_PLAYER_LEVEL, &plv_handler },
        { GRAPHICAL_FREQUENCY, &sgt_handler },
        { GRAPHICAL_CHANGE_FREQ, &sst_handler },
};

#endif
