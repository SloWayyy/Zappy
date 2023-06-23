/*
** EPITECH PROJECT, 2023
** server
** File description:
** flags.c
*/

#include <stdbool.h>
#include <stdio.h>

#include "args.h"
#include "constants.h"
#include "types.h"

int debug_handler(UNUSED int argc, UNUSED char const *argv[], \
    options_t *options, UNUSED int idx)
{
    if (options->debug) {
        fprintf(stderr, "Error: Debug mode is already set\n");
        return -1;
    }
    options->debug = true;
    return 0;
}

int immortal_handler(UNUSED int argc, UNUSED char const *argv[], \
    options_t *options, UNUSED int idx)
{
    if (options->immortal) {
        fprintf(stderr, "Error: Immortal mode is already set\n");
        return -1;
    }
    options->immortal = true;
    return 0;
}

int seed_handler(int argc, char const *argv[], options_t *options, int idx)
{
    if (argc <= idx + 1) {
        fprintf(stderr, "Error: %s requires an argument\n", argv[idx]);
        return -1;
    }
    if (options->seed != 0) {
        fprintf(stderr, "Error: Seed already set\n");
        return -1;
    }
    if (!check_positive(argv[idx + 1], "Seed", &options->seed)) {
        return -1;
    }
    return 1;
}
