/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** test_utils.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <unistd.h>

#include "buffer.h"
#include "server.h"
#include "tests.h"

Test(server, startup, .timeout = 5, .init=cr_redirect_stdout)
{
    char *argv[] = { "./zappy_server", "-p", "8000", NULL };
    int res = 0;
    pid_t pid = launch_server(argv);

    usleep(1000000);
    exit_server(pid);
    cr_assert_eq(res, 0);
}

Test(server, unknown_client, .timeout = 5, .init=cr_redirect_stdout)
{
    char *argv[] = { "./zappy_server", "-p", "8001", NULL };
    pthread_t thread;
    pid_t pid = launch_server(argv);
    routine_t *client = launch_client(&thread, 8001);

    execute_command(client, "test");
    usleep(1000);
    get_output(client);
    usleep(1000);
    exit_server(pid);
    exit_client(&thread, client);
    cr_assert_str_eq(client->buffer, "WELCOME\nko\n");
}

Test(server, graphic_client_default, .timeout = 5, .init=cr_redirect_stdout)
{
    char *argv[] = { "./zappy_server", "-p", "8002", NULL };
    pthread_t thread;
    pid_t pid = launch_server(argv);
    routine_t *client = launch_client(&thread, 8002);
    buffer_t *buffer = new_buffer();
    char *resource_line = strdup("bct x y");

    cr_assert_not_null(buffer);
    execute_command(client, "GRAPHIC");
    usleep(1000);
    get_output(client);
    usleep(1000);
    exit_server(pid);
    exit_client(&thread, client);
    append_buffer(buffer, "%s", client->buffer);
    cr_assert_str_eq(extract_line(buffer), "WELCOME");
    cr_assert_str_eq(extract_line(buffer), "msz 10 10");
    cr_assert_str_eq(extract_line(buffer), "sgt 100");
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            resource_line[4] = j + '0';
            resource_line[6] = i + '0';
            cr_assert_eq(strncmp(extract_line(buffer), resource_line, strlen(resource_line)), 0);
        }
    }
}

Test(server, single_tile, .timeout = 5, .init=cr_redirect_stdout)
{
    char *argv[] = { "./zappy_server", "-p", "8003", "--debug", "-x", "1", "-y", "1", NULL };
    pthread_t thread;
    pid_t pid = launch_server(argv);
    routine_t *client = launch_client(&thread, 8003);

    execute_command(client, "GRAPHIC");
    usleep(1000);
    get_output(client);
    usleep(1000);
    exit_server(pid);
    exit_client(&thread, client);
    fflush(stdout);
    cr_assert_stdout_eq_str(get_file_content("tests/samples/single_tile_server.txt"));
    cr_assert_str_eq(client->buffer, get_file_content("tests/samples/single_tile_client.txt"));
}
