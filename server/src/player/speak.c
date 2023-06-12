/*
** EPITECH PROJECT, 2023
** server
** File description:
** speak.c
*/

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/queue.h>

#include "constants.h"
#include "graphical.h"
#include "player.h"
#include "server.h"
#include "types.h"
#include "util.h"

static vector_t get_shortest(tile_t *sender_pos, tile_t *receiver_pos, \
    int width, int height)
{
    int x_norm = (int) receiver_pos->x - (int) sender_pos->x;
    int x_alter = (int) (receiver_pos->x) - (int) sender_pos->x - width;
    int y_norm = (int) receiver_pos->y - (int) sender_pos->y;
    int y_alter = (int) receiver_pos->y - (int) sender_pos->y - height;
    bool invert_x = x_norm > abs(x_alter);
    bool invert_y = y_norm > abs(y_alter);
    vector_t shortest = {
            invert_x ? x_alter : x_norm,
            invert_y ? y_alter : y_norm
    };

    return shortest;
}

static int get_angle(server_t *server, tile_t *sender_pos, player_t *receiver)
{
    vector_t target = get_direction(receiver->direction);
    vector_t shortest = get_shortest(sender_pos, receiver->pos, \
        server->options->width, server->options->height);
    int dot = target.x * shortest.x + target.y * shortest.y;
    int det = target.x * shortest.y - target.y * shortest.x;
    double angle = atan2(det, dot);
    double degrees = angle * (180.0 / M_PI);

    return degrees < 0 ? degrees + 360.0 : degrees;
}

static int get_source(server_t *server, tile_t *sender_pos, player_t *target)
{
    double degrees = 0.0;

    if (sender_pos->x == target->pos->x && sender_pos->y == target->pos->y) {
        return 0;
    }
    degrees = get_angle(server, sender_pos, target);
    printf("Angle: %f\n", degrees);
    for (size_t i = 0; i < DIRECTIONS_COUNT; i++) {
        if (degrees >= DIRECTIONS[i].min && degrees < DIRECTIONS[i].max) {
            return DIRECTIONS[i].num;
        }
    }
    return 1;
}

static void broadcast_player(server_t *server, client_t *sender, \
    client_t *receiver, char *message)
{
    int source = get_source(server, sender->player->pos, receiver->player);

    append_buffer(receiver->buffer_out, "%s %d, %s%s", \
        PLAYER_MESSAGE, source, message, LINE_BREAK);
}

static void broadcast_callback(server_t *server, client_t *client, void *arg)
{
    char *message = (char *) arg;
    client_t *node = NULL;

    SLIST_FOREACH(node, server->clients, next) {
        if (node->type == PLAYER && client != node) {
            broadcast_player(server, client, node, message);
        }
    }
    send_graphical_event(server, "%s %zu %s%s", \
        GRAPHICAL_PLAYER_BROADCAST, client->player->id, message, LINE_BREAK);
    append_buffer(client->buffer_out, "%s%s", \
        PLAYER_OK, LINE_BREAK);
    flush_command(server, client);
}

bool broadcast_handler(server_t *server, client_t *client, char *line)
{
    char *message = NULL;
    size_t len = strlen(line);
    size_t prefix = strlen(PLAYER_BROADCAST);
    size_t message_len = len - prefix;

    if (len < strlen(PLAYER_BROADCAST) + 2) {
        return false;
    }
    message = malloc(sizeof(char) * message_len);
    strcpy(message, &line[prefix + 1]);
    message[message_len - 1] = '\0';
    setup_task(client->player->action_task, &broadcast_callback, message);
    schedule_task(client->player->action_task, server, BROADCAST_DELAY, 1);
    return true;
}
