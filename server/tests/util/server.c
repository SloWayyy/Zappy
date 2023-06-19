/*
** EPITECH PROJECT, 2023
** server
** File description:
** server.c
*/

#include <criterion/criterion.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>

#include "tests.h"

pid_t launch_server(char **argv)
{
    char *env[] = { NULL };
    pid_t pid = fork();

    cr_assert_neq(pid, -1, "Error: Could not fork");
    if (pid == 0) {
        execve(argv[0], argv, env);
        _exit(84);
    } else {
        return pid;
    }
}

void exit_server(pid_t pid)
{
    int res = kill(pid, SIGINT);

    cr_assert_neq(res, -1, "Error: Could not kill server");
    waitpid(pid, &res, 0);
    cr_assert_eq(WEXITSTATUS(res), 0, "Server did not exit properly");
}
