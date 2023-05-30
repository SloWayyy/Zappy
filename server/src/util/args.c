/*
** EPITECH PROJECT, 2023
** server
** File description:
** args.c
*/

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "args.h"
#include "constants.h"
#include "types.h"

static void auto_fill(options_t *options)
{
    if (options->port == 0) {
        options->port = DEFAULT_PORT;
        printf("No port set, default port is %d\n", DEFAULT_PORT);
    }
    if (options->width == 0 && options->height == 0) {
        options->width = DEFAULT_WIDTH;
        options->height = DEFAULT_HEIGHT;
        printf("No map dimensions set, default is %dx%d\n", \
            DEFAULT_WIDTH, DEFAULT_HEIGHT);
    }
    if (options->clientsNb == 0) {
        options->clientsNb = DEFAULT_CLIENTS;
        printf("No client number set, default client number is %d\n", \
            DEFAULT_CLIENTS);
    }
    if (options->freq == 0) {
        options->freq = DEFAULT_FREQ;
        printf("No frequency set, default frequency is %dms\n", DEFAULT_FREQ);
    }
}

static bool post_check(options_t *options)
{
    int map = (options->width != 0) + (options->height != 0);

    if (options->names == NULL) {
        fprintf(stderr, "Error: Team names are not set\n");
        return false;
    }
    if (map == 1) {
        fprintf(stderr, "Error: Map dimensions are not set\n");
        return false;
    }
    auto_fill(options);
    return true;
}

static int handle_argument(int argc, char **argv, options_t *options, int index)
{
    int shortOpt = 0;
    int longOpt = 0;

    for (size_t i = 0; i < OPTIONS_COUNT; i++) {
        shortOpt = 0;
        longOpt = 0;
        if (HANDLERS[i].shortOpt != NULL) {
            shortOpt = strcmp(argv[index], HANDLERS[i].shortOpt);
        }
        if (HANDLERS[i].longOpt != NULL) {
            longOpt = strcmp(argv[index], HANDLERS[i].longOpt);
        }
        if (shortOpt == 0 || longOpt == 0) {
            return HANDLERS[i].function(argc, argv, options, index);
        }
    }
    fprintf(stderr, "Error: Unknown option: %s\n", argv[index]);
    return -1;
}

bool check_arguments(int argc, char **argv, options_t *options)
{
    int index = 0;

    for (int i = 1; i < argc; ++i) {
        index = handle_argument(argc, argv, options, i);
        if (index == -1) {
            return false;
        }
        i += index;
    }
    return post_check(options);
}
