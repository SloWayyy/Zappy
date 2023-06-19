/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** test_utils.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <fcntl.h>
#include <unistd.h>

#include "server.h"
#include "tests.h"

Test(server, startup, .timeout = 10, .init=cr_redirect_stdout)
{
    char *argv[] = { "./zappy_server", "-p", "8000", NULL };
    int res = 0;
    pid_t pid = launch_server(argv);

    usleep(2000000);
    exit_server(pid);
    cr_assert_eq(res, 0);
}

Test(server, unknown_client, .timeout = 10, .init=cr_redirect_stdout)
{
    char *argv[] = { "./zappy_server", "-p", "8001", NULL };
    pthread_t thread;
    pid_t pid = launch_server(argv);
    routine_t *client = launch_client(&thread, 8001);

    execute_command(client, "test");
    usleep(100);
    get_output(client);
    exit_server(pid);
    exit_client(&thread, client);
    cr_assert_str_eq(client->buffer, "WELCOME\nko\n");
}
