/*
** EPITECH PROJECT, 2023
** server
** File description:
** util.h
*/

#ifndef UTILS_H_
    #define UTILS_H_

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

#endif
