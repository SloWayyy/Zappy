/*
** EPITECH PROJECT, 2023
** server
** File description:
** buffer.c
*/

#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "constants.h"
#include "types.h"

bool resize_buffer(buffer_t *buffer)
{
    buffer->buffer = realloc(buffer->buffer, buffer->capacity);
    if (buffer->buffer == NULL) {
        perror("realloc failed");
        return false;
    }
    memset(&buffer->buffer[buffer->size], 0, buffer->capacity - buffer->size);
    return true;
}

void vappend_buffer(buffer_t *buffer, char const *format, va_list args)
{
    bool resize = false;
    size_t len;
    va_list copy;

    va_copy(copy, args);
    len = vsnprintf(NULL, 0, format, args);
    while (buffer->size + len >= buffer->capacity) {
        resize = true;
        buffer->capacity += BUFFER_EXTRA;
    }
    if (resize && !resize_buffer(buffer)) {
        return;
    }
    vsprintf(&buffer->buffer[buffer->size], format, copy);
    buffer->size += len;
    va_end(copy);
}

void append_buffer(buffer_t *buffer, char const *format, ...)
{
    va_list args;

    va_start(args, format);
    vappend_buffer(buffer, format, args);
    va_end(args);
}

bool dump_buffer(buffer_t *buffer, int fd)
{
    write(fd, buffer->buffer, buffer->size);
    buffer->size = 0;
    if (buffer->capacity > BUFFER_SIZE) {
        buffer->capacity = BUFFER_SIZE;
        return resize_buffer(buffer);
    }
    return true;
}
