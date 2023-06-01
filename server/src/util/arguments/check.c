/*
** EPITECH PROJECT, 2023
** server
** File description:
** args_check.c
*/

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "constants.h"
#include "types.h"

bool check_number(char const *str, char *option, int *storage)
{
    char *end = NULL;
    long parsed = strtol(str, &end, 10);

    if (strlen(end) > 0) {
        printf("Error: %s must be a number\n", option);
        return false;
    }
    *storage = (int) parsed;
    return true;
}

bool check_port(char *str, int *storage)
{
    if (!check_number(str, "Port", storage)) {
        return false;
    }
    if (*storage < 1 || *storage >= MAX_PORT) {
        printf("Error: Port must be between 1 and %d\n", (MAX_PORT - 1));
        return false;
    }
    return true;
}

bool check_positive(char const *str, char *option, int *storage)
{
    if (!check_number(str, option, storage)) {
        return false;
    }
    if (*storage < 1) {
        printf("Error: %s must be positive\n", option);
        return false;
    }
    return true;
}
