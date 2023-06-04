/*
** EPITECH PROJECT, 2023
** server
** File description:
** objects.h
*/

#ifndef OBJECTS_H_
    #define OBJECTS_H_

    #include "types.h"

client_t *new_client(int fd, FILE *stream);
void close_client(client_t *client);
void free_client(client_t *client);
void free_clients(server_t *server);

team_t *new_team(char const *name, size_t max_players);
void free_team(team_t *team);
void free_teams(server_t *server);

player_t *new_player(void);
void free_player(player_t *player);

#endif
