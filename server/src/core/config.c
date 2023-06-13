/*
** EPITECH PROJECT, 2023
** server
** File description:
** config.c
*/

#include "types.h"

char const *resources_map[RESOURCES_TYPES_QUANTITY] = {
        "food",
        "linemate",
        "deraumere",
        "sibur",
        "mendiane",
        "phiras",
        "thystame",
};

const double resources_density[RESOURCES_TYPES_QUANTITY] = {
        0.5,
        0.3,
        0.15,
        0.1,
        0.1,
        0.08,
        0.05,
};
