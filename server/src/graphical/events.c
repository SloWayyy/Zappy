/*
** EPITECH PROJECT, 2023
** server
** File description:
** events.c
*/

#include <stdarg.h>

#include "server.h"
#include "util.h"

void send_graphical_event(server_t *server, const char *format, ...)
{
    va_list list;
    client_t *node = NULL;

    va_start(list, format);
    SLIST_FOREACH(node, server->clients, next) {
        if (node->type == GRAPHIC) {
            vappend_buffer(node->buffer, format, list);
        }
    }
}
