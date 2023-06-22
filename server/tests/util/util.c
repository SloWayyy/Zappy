/*
** EPITECH PROJECT, 2023
** server
** File description:
** util.c
*/

#include <criterion/criterion.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

char *get_file_content(char *filepath)
{
    int fd = open(filepath, O_RDONLY);
    char *content = NULL;
    struct stat stats;

    cr_assert_neq(fd, -1, "Error: Could not open %s", filepath);
    cr_assert_neq(stat(filepath, &stats), -1, "Error: Could not stat %s", filepath);
    content = malloc(sizeof(char) * (stats.st_size + 1));
    cr_assert_not_null(content, "Error: Could not allocate memory");
    cr_assert_eq(read(fd, content, stats.st_size), stats.st_size, "Error: Could not read %s", filepath);
    content[stats.st_size] = '\0';
    close(fd);
    return content;
}
