/*
** EPITECH PROJECT, 2023
** server
** File description:
** util.h
*/

#ifndef UTILS_H_
    #define UTILS_H_

    #define DIRECTIONS_COUNT (sizeof(DIRECTIONS) / sizeof(direction_t))

    #include <arpa/inet.h>
    #include <stdarg.h>
    #include <stdbool.h>
    #include <stddef.h>

    #include "types.h"

typedef struct vector {
    int x;
    int y;
} vector_t;

size_t array_len(char **array);
void free_array(char **array);

void append_buffer(buffer_t *buffer, char const *format, ...);
void vappend_buffer(buffer_t *buffer, char const *format, va_list list);
bool dump_buffer(buffer_t *buffer, int fd);
char *extract_line(buffer_t *buffer);
bool resize_buffer(buffer_t *buffer);

vector_t get_direction(direction_type_t direction);

struct sockaddr *generate_address(int port, char *address);
void get_elapsed_time(struct timeval *start, struct timeval *end, \
    struct timeval *ptr);

typedef struct direction {
    int min;
    int max;
    int num;
} direction_t;

static const direction_t DIRECTIONS[] = {
        { 0, 30, 1 },
        { 30, 60, 8 },
        { 60, 120, 7 },
        { 120, 150, 6 },
        { 150, 210, 5 },
        { 210, 240, 4 },
        { 240, 300, 3 },
        { 300, 330, 2 },
        { 330, 360, 1 },
};

#endif
