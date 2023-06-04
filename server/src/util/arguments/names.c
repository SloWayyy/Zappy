/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** This file will handle the arguments -n
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "args.h"

static bool is_valid(const char **teams, int size, char const *name)
{
    for (int i = 0; i < size; i++) {
        if (strcmp(teams[i], name) == 0) {
            fprintf(stderr, "Error: Team %s is registered twice\n", name);
            return true;
        }
    }
    return false;
}

static int fill_names(char const *argv[], int padding, int quantity, \
    const char **array)
{
    for (int i = 0; i < quantity; i++) {
        if (is_valid(array, i, argv[padding + i]) == 1) {
            return -1;
        }
        array[i] = argv[padding + i];
    }
    array[quantity] = NULL;
    return quantity;
}

int names_handler(int argc, char const *argv[], options_t *options, int idx)
{
    int args = 0;

    if (options->names != NULL) {
        fprintf(stderr, "Error: Team names are already set\n");
        return -1;
    }
    for (int i = idx + 1; i < argc && argv[i][0] != '-'; i++) {
        args++;
    }
    if (args == 0) {
        fprintf(stderr, "Error: No team names given\n");
        return -1;
    }
    options->names = malloc(sizeof(char *) * (args + 1));
    if (options->names == NULL) {
        perror("malloc failed");
        return -1;
    }
    return fill_names(argv, idx + 1, args, options->names);
}
