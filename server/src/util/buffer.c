/*
** EPITECH PROJECT, 2023
** server
** File description:
** buffer.c
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "constants.h"
#include "types.h"
#include "util.h"

static bool resize_buffer(buffer_t *buffer)
{
    buffer->buffer = realloc(buffer->buffer, buffer->capacity);
    if (buffer->buffer == NULL) {
        perror("realloc failed");
        return false;
    }
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

bool append_buffer(buffer_t *buffer, char const *str)
{
    size_t len = strlen(str);

    if (buffer->size + len >= buffer->capacity) {
        while (buffer->size + len >= buffer->capacity) {
            buffer->capacity += BUFFER_EXTRA;
        }
        if (!resize_buffer(buffer)) {
            return false;
        }
    }
    memcpy(buffer->buffer + buffer->size, str, len);
    buffer->size += len;
    return true;
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

void free_buffer(buffer_t *buffer)
{
    free(buffer->buffer);
    free(buffer);
}
