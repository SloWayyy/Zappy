/*
** EPITECH PROJECT, 2023
** server
** File description:
** util.h
*/

#ifndef UTILS_H_
    #define UTILS_H_

    #include <stddef.h>

// ARRAYS
size_t array_len(char **array);
void free_array(char **array);
char **str_to_word(char const *str, char separator);

#endif