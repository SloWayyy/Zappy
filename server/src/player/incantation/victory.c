/*
** EPITECH PROJECT, 2023
** server
** File description:
** victory.c
*/

#include <stdbool.h>
#include <stdlib.h>
#include <sys/queue.h>

#include "buffer.h"
#include "constants.h"
#include "graphical.h"
#include "player.h"
#include "types.h"

static void select_winning_team(server_t *server, team_t **teams, size_t size)
{
    size_t num = rand() % size;
    team_t *winner = teams[num];

    server->zappy->win = true;
    send_graphical_event(server, "%s %s%s", \
        GRAPHICAL_VICTORY, winner->name, LINE_BREAK);
    debug(server, "Team %s won the game", winner->name);
}

static void filter_winning_teams(team_t **teams, size_t *size)
{
    size_t players = 0;
    player_t *node = NULL;

    for (size_t i = 0; i < *size; i++) {
        players = 0;
        SLIST_FOREACH(node, teams[i]->players, next_team) {
            players += node->level == VICTORY_LEVEL;
        }
        if (players < VICTORY_PLAYERS) {
            teams[i] = teams[*size - 1];
            teams[*size - 1] = NULL;
            *size -= 1;
            i--;
        }
    }
}

static bool add_team_to_check(player_t *player, team_t ***teams, size_t *size)
{
    if (player->level != VICTORY_LEVEL) {
        return true;
    }
    for (size_t i = 0; i < *size; i++) {
        if ((*teams)[i] == player->team) {
            return true;
        }
    }
    *size += 1;
    *teams = realloc(*teams, sizeof(team_t *) * *size);
    if (*teams == NULL) {
        return false;
    }
    (*teams)[*size - 1] = player->team;
    return true;
}

void check_victory(server_t *server, incantation_t *incantation)
{
    size_t size = 0;
    player_t *player = NULL;
    team_t **teams = NULL;

    if (server->zappy->win)
        return;
    SLIST_FOREACH(player, &incantation->players, next_incantation) {
        if (!add_team_to_check(player, &teams, &size)) {
            free(teams);
            return;
        }
    }
    if (size == 0) {
        return;
    }
    filter_winning_teams(teams, &size);
    if (size > 0) {
        select_winning_team(server, teams, size);
    }
    free(teams);
}
