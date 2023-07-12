/*
** EPITECH PROJECT, 2023
** server
** File description:
** buffer_in.cpp
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "buffer.h"
#include "constants.h"

static bool remove_line(buffer_t *buffer, size_t size)
{
    memset(buffer->buffer, 0, size + 1);
    memmove(buffer->buffer, &buffer->buffer[size + 1], buffer->size - size - 1);
    buffer->size -= size + 1;
    if (buffer->capacity > BUFFER_SIZE && buffer->size < BUFFER_SIZE) {
        buffer->capacity = BUFFER_SIZE;
        return resize_buffer(buffer);
    }
    return true;
}

static char *copy_line(buffer_t *buffer, size_t size)
{
    char *line = malloc(sizeof(char) * (size + 1));

    if (line == NULL) {
        perror("malloc failed");
        return NULL;
    }
    memset(line, 0, size + 1);
    strncpy(line, buffer->buffer, size);
    return line;
}

char *extract_line(buffer_t *buffer)
{
    int index = -1;
    char *line = NULL;

    for (size_t i = 0; i < buffer->size && index == -1; i++) {
        if (buffer->buffer[i] == '\n') {
            index = i;
        }
    }
    if (index == -1) {
        return NULL;
    }
    line = copy_line(buffer, index);
    if (line == NULL) {
        return NULL;
    }
    if (!remove_line(buffer, index)) {
        free(line);
        return NULL;
    }
    return line;
}
