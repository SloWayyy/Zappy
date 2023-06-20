/*
** EPITECH PROJECT, 2023
** server
** File description:
** flags.c
*/

#include <stdio.h>

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
