/*
** EPITECH PROJECT, 2023
** strrr
** File description:
** strrr
*/

#include <stdlib.h>

void free_array(char **array)
{
    for (unsigned int i = 0; array[i] != NULL; i++)
        free(array[i]);
    free(array);
}

size_t array_len(char **array)
{
    size_t len = 0;

    for (; array[len] != NULL; len++);
    return len;
}
