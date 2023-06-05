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

static bool resize_buffer(buffer_t *buffer)
{
    buffer->buffer = realloc(buffer->buffer, buffer->capacity);
    if (buffer->buffer == NULL) {
        perror("realloc failed");
        return false;
    }
    memset(&buffer->buffer[buffer->size], 0, buffer->capacity - buffer->size);
    return true;
}

buffer_t *new_buffer(void)
{
    buffer_t *buffer = malloc(sizeof(buffer_t));

    if (buffer == NULL) {
        perror("malloc failed");
        return NULL;
    }
    buffer->buffer = malloc(sizeof(char) * BUFFER_SIZE);
    if (buffer->buffer == NULL) {
        perror("malloc failed");
        free(buffer);
        return NULL;
    }
    memset(buffer->buffer, 0, BUFFER_SIZE);
    buffer->size = 0;
    buffer->capacity = BUFFER_SIZE;
    return buffer;
}

void vappend_buffer(buffer_t *buffer, char const *format, va_list args)
{
    size_t len;
    va_list copy;
    va_copy(copy, args);

    len = vsnprintf(NULL, 0, format, args);
    while (buffer->size + len >= buffer->capacity) {
        buffer->capacity += BUFFER_EXTRA;
    }
    if (!resize_buffer(buffer)) {
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
