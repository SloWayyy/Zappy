/*
** EPITECH PROJECT, 2023
** server
** File description:
** player.h
*/

#ifndef PLAYER_H_
    #define PLAYER_H_

    #define PLAYER_UNKNOWN_COMMAND "ko\n"

    #include <stdbool.h>

    #include "types.h"

void handle_player_command(server_t *server, client_t *client, char *line);

bool try_join_team(server_t *server, client_t *client, char *line);

#endif
