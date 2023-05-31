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
int zappy_server(int argc, char const *argv[]);
bool check_arguments(int argc, char const *argv[], options_t *options);

// CHECKS
bool check_number(char const *str, char *option, int *storage);

#endif
