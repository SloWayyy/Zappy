/*
** EPITECH PROJECT, 2023
** server
** File description:
** args_check.c
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "constants.h"
#include "types.h"

bool check_number(char *str, char *option, int *storage)
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

bool check_positive(char *str, char *option, int *storage)
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

static void fill_names(char **argv, int padding, int quantity, char **array)
{
    for (int i = 0; i < quantity; i++) {
        array[i] = strdup(argv[padding + i]);
    }
    array[quantity] = NULL;
}

int names_handler(int argc, char **argv, options_t *options, int index)
{
    int args = 0;

    if (options->names != NULL) {
        fprintf(stderr, "Error: Team names are already set\n");
        return -1;
    }
    for (int i = index + 1; i < argc && argv[i][0] != '-'; i++) {
        args++;
    }
    if (args == 0) {
        fprintf(stderr, "Error: No team names given\n");
        return -1;
    }
    options->names = malloc(sizeof(char *) * (args + 1));
    if (options->names == NULL) {
        fprintf(stderr, "Error: malloc failed\n");
        return -1;
    }
    fill_names(argv, index + 1, args, options->names);
    return args;
}
