/*
** EPITECH PROJECT, 2022
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

static size_t count_word(char const *str, char sep)
{
    int count = 1;

    for (size_t i = 0; str[i] != '\0'; i++) {
        if (str[i] == sep && str[i + 1] != sep)
            count++;
    }
    return count;
}

static int size_word(char const *str, int i, char separator)
{
    int count = 0;

    for (; str[i] != separator && str[i] != '\0'; i++)
        count++;
    return count;
}

char **str_to_word(char const *str, char separator)
{
    char **tab = NULL;
    int i = 0;
    int size = 0;
    size_t count = count_word(str, separator);

    tab = malloc(sizeof(char *) * (count + 1));
    tab[count] = NULL;
    for (size_t y = 0; y != count; y++) {
        for (; str[i] == separator; i++);
        size = size_word(str, i, separator);
        tab[y] = malloc(sizeof(char) * (size + 1));
        tab[y][size] = '\0';
        for (int x = 0; x != size; x++) {
            tab[y][x] = str[i];
            i++;
        }
        i++;
    }
    return (tab);
}
