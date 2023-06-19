/*
** EPITECH PROJECT, 2023
** server
** File description:
** buffer.h
*/

#ifndef BUFFER_H_
    #define BUFFER_H_

    #include <stdarg.h>
    #include <stdbool.h>
    #include <stddef.h>

typedef struct buffer {
    char *buffer;
    size_t size;
    size_t capacity;
} buffer_t;

buffer_t *new_buffer(void);
void free_buffer(buffer_t *buffer);

char *extract_line(buffer_t *buffer);

void append_buffer(buffer_t *buffer, char const *format, ...);
void vappend_buffer(buffer_t *buffer, char const *format, va_list list);
bool dump_buffer(buffer_t *buffer, int fd);

bool resize_buffer(buffer_t *buffer);

#endif
