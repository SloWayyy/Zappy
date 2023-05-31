/*
** EPITECH PROJECT, 2023
** server
** File description:
** util.h
*/

#ifndef UTILS_H_
    #define UTILS_H_

    #include <arpa/inet.h>
    #include <stddef.h>

    #include "types.h"

size_t array_len(char **array);
void free_array(char **array);

buffer_t *new_buffer(void);
bool append_buffer(buffer_t *buffer, char const *str);
bool dump_buffer(buffer_t *buffer, int fd);
void free_buffer(buffer_t *buffer);

struct sockaddr *generate_address(int port, char *address);
void get_elapsed_time(struct timeval *start, struct timeval *end, \
    struct timeval *ptr);

#endif
