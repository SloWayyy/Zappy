/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** server.h
*/

#ifndef SERVER_H_
    #define SERVER_H_

    #include <stdbool.h>

    #include "types.h"

// CORE
int zappy_server(int argc, char **argv);
bool check_arguments(int argc, char **argv, options_t *options);

// CHECKS
bool check_number(char *str, char *option, int *storage);

#endif
