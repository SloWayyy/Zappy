/*
** EPITECH PROJECT, 2023
** server
** File description:
** args.h
*/

#ifndef ARGS_H
    #define ARGS_H

    #define OPTIONS_COUNT (sizeof(HANDLERS) / sizeof(option_t))

    #include <stdbool.h>

    #include "types.h"

bool check_port(char const *str, int *storage);
bool check_positive(char const *str, char *option, int *storage);

int port_handler(int argc, char const *argv[], options_t *options, int idx);
int width_handler(int argc, char const *argv[], options_t *options, int idx);
int height_handler(int argc, char const *argv[], options_t *options, int idx);
int names_handler(int argc, char const *argv[], options_t *options, int idx);
int clients_handler(int argc, char const *argv[], options_t *options, int idx);
int freq_handler(int argc, char const *argv[], options_t *options, int idx);
int debug_handler(int argc, char const *argv[], options_t *options, int idx);
int immortal_handler(int argc, char const *argv[], options_t *options, int idx);

typedef int (options_handler_t) \
    (int argc, char const *argv[], options_t *options, int index);

typedef struct option {
    char const *shortOpt;
    char const *longOpt;
    options_handler_t *function;
} option_t;

static const option_t HANDLERS[] = {
        { "-p", "--port", &port_handler },
        { "-x", "--width", &width_handler },
        { "-y", "--height", &height_handler },
        { "-n", "--names", &names_handler },
        { "-c", "--clients", &clients_handler },
        { "-f", "--freq", &freq_handler },
        { NULL, "--debug", &debug_handler },
        { NULL, "--immortal", &immortal_handler },
};

#endif
