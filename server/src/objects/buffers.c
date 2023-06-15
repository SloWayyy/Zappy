/*
** EPITECH PROJECT, 2023
** server
** File description:
** buffers.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "buffer.h"
#include "constants.h"

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

void free_buffer(buffer_t *buffer)
{
    free(buffer->buffer);
    free(buffer);
}
