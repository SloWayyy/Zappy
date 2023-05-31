/*
** EPITECH PROJECT, 2023
** server
** File description:
** types.h
*/

#ifndef TYPES_H_
    #define TYPES_H_

typedef struct options_s {
    int port;
    int width;
    int height;
    char **names;
    int clientsNb;
    int freq;
} options_t;

#endif
