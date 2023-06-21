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

process_t *launch_server(char **argv)
{
    int pipefd[2];
    char *env[] = { NULL };
    process_t *process = malloc(sizeof(process_t));

    cr_assert_neq(pipe(pipefd), -1, "Error: pipe failed");
    cr_assert_not_null(process, "Error: malloc failed");
    process->stdin_fd = pipefd[1];
    process->pid = fork();
    cr_assert_neq(process->pid, -1, "Error: fork failed");
    if (process->pid == 0) {
        dup2(pipefd[0], STDIN_FILENO);
        execve(argv[0], argv, env);
        _exit(42);
    } else {
        return process;
    }
}

void execute_server_command(process_t *process, char *command)
{
    cr_assert_eq(write(process->stdin_fd, command, strlen(command)), (ssize_t) strlen(command), "Error: write failed");
    cr_assert_eq(write(process->stdin_fd, "\n", 1), 1, "Error: write failed");
    usleep(50000);
}

void exit_server(process_t *process)
{
    int res = kill(process->pid, SIGINT);
    int status = 0;

    cr_assert_neq(res, -1, "Error: Could not kill server");
    waitpid(process->pid, &status, 0);
    res = WEXITSTATUS(status);
    cr_assert_neq(res, 42, "Error: Server did not start");
    cr_assert_eq(res, 0, "Error: Server did not exit properly (%d)", res);
}
