/*
** EPITECH PROJECT, 2023
** server
** File description:
** incantation.c
*/

#include <stdbool.h>
#include <stdlib.h>

#include "constants.h"
#include "player.h"
#include "server.h"
#include "types.h"

static bool meet_requirements(server_t *server, tile_t *tile,
    const incantation_requirements_t *requirements)
{
    return true;
}

static void incantation_callback(server_t *server, client_t *client, void *arg)
{
    incantation_t *incantation = (incantation_t *) arg;
}

bool incantation_handler(server_t *server, client_t *client, UNUSED char *line)
{
    const incantation_requirements_t *requirements = NULL;
    incantation_t *incantation = NULL;

    for (size_t i = 0; i < INCANTATIONS_COUNT && requirements == NULL; i++) {
        if (INCANTATIONS[i].level == client->player->level) {
            requirements = &INCANTATIONS[i];
        }
    }
    if (requirements == NULL || !meet_requirements(server, \
        client->player->pos, requirements)) {
        return false;
    }
    incantation = setup_incantation(client->player, requirements);
    if (incantation == NULL) {
        return false;
    }
    setup_task(client->player->action_task, &incantation_callback, NULL);
    schedule_task(client->player->action_task, server, INCANTATION_DELAY, 1);
    return true;
}
