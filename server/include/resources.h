/*
** EPITECH PROJECT, 2023
** server
** File description:
** resources.c
*/

#ifndef RESOURCES_H_
    #define RESOURCES_H_


    #define INCANTATIONS_COUNT \
        (sizeof(INCANTATIONS) / sizeof(incantation_requirements_t))
    #define RESOURCES_TYPES_QUANTITY (sizeof(RESOURCES) / sizeof(resource_t))

    #include <stdbool.h>

typedef enum resource_type {
    FOOD,
    LINEMATE,
    DERAUMERE,
    SIBUR,
    MENDIANE,
    PHIRAS,
    THYSTAME,
} resource_type_t;

typedef struct resource {
    char const *name;
    double density;
} resource_t;

static const resource_t RESOURCES[] = {
        { "food", 0.5 },
        { "linemate", 0.3 },
        { "deraumere", 0.15 },
        { "sibur", 0.1 },
        { "mendiane", 0.1 },
        { "phiras", 0.08 },
        { "thystame", 0.05 },
};

typedef struct incantation_requirement {
    size_t level;
    size_t players_nb;
    size_t resources[RESOURCES_TYPES_QUANTITY];
} incantation_requirements_t;

static const incantation_requirements_t INCANTATIONS[] = {
        { 1, 1, { 0, 1, 0, 0, 0, 0, 0 } },
        { 2, 2, { 0, 1, 1, 1, 0, 0, 0 } },
        { 3, 2, { 0, 2, 0, 1, 0, 2, 0 } },
        { 4, 4, { 0, 1, 1, 2, 0, 1, 0 } },
        { 5, 4, { 0, 1, 2, 1, 3, 0, 0 } },
        { 6, 6, { 0, 1, 2, 3, 0, 1, 0 } },
        { 7, 6, { 0, 2, 2, 2, 2, 2, 1 } },
};

#endif
