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
void free_client(server_t *server, client_t *client);
void free_clients(server_t *server);
client_t *get_client_by_player_id(server_t *server, size_t id);

team_t *new_team(char const *name, size_t max_players);
void free_team(team_t *team);
void free_teams(server_t *server);

player_t *new_player(void);
void free_player(player_t *player);

buffer_t *new_buffer(void);
void free_buffer(buffer_t *buffer);

#endif
