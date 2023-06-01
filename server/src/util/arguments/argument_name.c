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

static int team_already_exist(char **team_name, char const *name)
{
    for (int i = 0; team_name[i] != NULL; i++) {
        if (strcmp(team_name[i], name) == 0) {
            fprintf(stderr, "Error: Team name already exist\n");
            return 1;
        }
    }
    return 0;
}

static int fill_names(char const *argv[], int padding, int quantity, \
    char **array)
{
    for (int i = 0; i < quantity; i++) {
        if (i != 0 && team_already_exist(array, argv[padding + i]) == 1)
            return -1;
        else
            array[i] = strdup(argv[padding + i]);
    }
    array[quantity] = NULL;
    return 0;
}

static void count_number_team(int argc, char const *argv[], int idx, int *args)
{
    for (int i = idx + 1; i < argc && argv[i][0] != '-'; i++)
        *args += 1;
}

int names_handler(int argc, char const *argv[], options_t *options, int idx)
{
    int args = 0;

    if (options->names != NULL) {
        fprintf(stderr, "Error: Team names are already set\n");
        return -1;
    }
    count_number_team(argc, argv, idx, &args);
    if (args == 0) {
        fprintf(stderr, "Error: No team names given\n");
        return -1;
    }
    options->names = malloc(sizeof(char *) * (args + 1));
    if (options->names == NULL) {
        fprintf(stderr, "Error: malloc failed\n");
        return -1;
    }
    return (fill_names(argv, idx + 1, args, options->names)) == -1 ? -1 : args;
}
