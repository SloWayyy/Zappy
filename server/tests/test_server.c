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
    get_output(client);
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
    cr_assert_not_null(resource_line);
    execute_command(client, "GRAPHIC");
    get_output(client);
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
    get_output(client);
    exit_server(pid);
    exit_client(&thread, client);
    fflush(stdout);
    cr_assert_stdout_eq_str(get_file_content("tests/samples/single_tile_server.txt"));
    cr_assert_str_eq(client->buffer, get_file_content("tests/samples/single_tile_client.txt"));
}

Test(server, graphical_tick, .timeout = 5, .init=cr_redirect_stdout)
{
    char *argv[] = { "./zappy_server", "-p", "8004", "-x", "1", "-y", "1", NULL };
    pthread_t thread;
    pid_t pid = launch_server(argv);
    routine_t *client = launch_client(&thread, 8004);

    execute_command(client, "sgt");
    execute_command(client, "GRAPHIC");
    execute_command(client, "sgt 100");
    execute_command(client, "sgt");
    execute_command(client, "sst");
    execute_command(client, "sst 10 10");
    execute_command(client, "sst 10a");
    execute_command(client, "sst -10");
    execute_command(client, "sst 9999999");
    execute_command(client, "sst 10");
    execute_command(client, "sgt");
    get_output(client);
    exit_server(pid);
    exit_client(&thread, client);
    cr_assert_str_eq(client->buffer, get_file_content("tests/samples/tick_client.txt"));
}

Test(server, graphical_infos, .timeout = 5, .init=cr_redirect_stdout)
{
    char *argv[] = { "./zappy_server", "-p", "8005", "-x", "1", "-y", "1", NULL };
    pthread_t thread;
    pid_t pid = launch_server(argv);
    routine_t *client = launch_client(&thread, 8005);

    execute_command(client, "GRAPHIC");
    execute_command(client, "abc");
    execute_command(client, "msz");
    execute_command(client, "msz aaa");
    execute_command(client, "bct 0 0");
    get_output(client);
    exit_server(pid);
    exit_client(&thread, client);
    cr_assert_str_eq(client->buffer, get_file_content("tests/samples/infos_client.txt"));
}

Test(server, player_connection, .timeout = 5, .init=cr_redirect_stdout)
{
    char *argv[] = { "./zappy_server", "-p", "8006", "-x", "1", "-y", "1", NULL };
    pthread_t thread;
    pthread_t thread_player;
    pid_t pid = launch_server(argv);
    routine_t *client = launch_client(&thread, 8006);
    routine_t *player = launch_client(&thread_player, 8006);
    buffer_t *buffer = new_buffer();
    int idx = 0;
    char *line = NULL;
    char *egg_lines[4] = { "ebo 0", "ebo 1", "ebo 2", "ebo 3" };
    char *player_lines[4] = { "pnw 0 0 0 1 1 Team1", "pnw 0 0 0 2 1 Team1", "pnw 0 0 0 3 1 Team1", "pnw 0 0 0 4 1 Team1" };

    cr_assert_not_null(buffer);
    execute_command(client, "GRAPHIC");
    get_output(client);
    execute_command(player, "Team1");
    get_output(client);
    get_output(player);
    exit_server(pid);
    exit_client(&thread, client);
    append_buffer(buffer, "%s", client->buffer);
    line = extract_line(buffer);
    cr_assert_not_null(line);
    for (idx = 0; idx < 4 && strcmp(line, egg_lines[idx]) != 0; idx++);
    cr_assert_neq(idx, 4);
    line = extract_line(buffer);
    cr_assert_not_null(line);
    for (idx = 0; idx < 4 && strcmp(line, player_lines[idx]) != 0; idx++);
    cr_assert_neq(idx, 4);
    cr_assert_null(extract_line(buffer));
}

Test(server, player_death, .timeout = 5, .init=cr_redirect_stdout)
{
    char *argv[] = { "./zappy_server", "-p", "8007", "-f", "5000", NULL };
    pthread_t thread;
    pthread_t thread_player;
    pid_t pid = launch_server(argv);
    routine_t *client = launch_client(&thread, 8007);
    routine_t *player = launch_client(&thread_player, 8007);

    execute_command(client, "GRAPHIC");
    execute_command(player, "Team1");
    get_output(client);
    get_output(player);
    usleep(500000);
    get_output(client);
    get_output(player);
    exit_server(pid);
    exit_client(&thread, client);
    exit_client(&thread, player);
    cr_assert_str_eq(player->buffer, "dead\n");
    cr_assert_str_eq(client->buffer, "pdi 0\n");
}

Test(server, player_incantation, .timeout = 5, .init=cr_redirect_stdout)
{
    char *argv[] = { "./zappy_server", "-p", "8008", "-f", "5000", "--seed", "4000", "--immortal", "--debug", NULL };
    pthread_t thread;
    pthread_t thread_player;
    pid_t pid = launch_server(argv);
    routine_t *client = launch_client(&thread, 8008);
    routine_t *player = launch_client(&thread_player, 8008);

    execute_command(client, "GRAPHIC");
    execute_command(player, "Team1");
    execute_command(player, "Look");
    execute_command(player, "Forward\nLeft\nForward");
    execute_command(player, "Look");
    execute_command(player, "Incantation");
    execute_command(player, "Look");
    execute_command(player, "Incantation");
    usleep(500000);
    get_output(client);
    get_output(player);
    exit_server(pid);
    exit_client(&thread, client);
    exit_client(&thread, player);
    fflush(stdout);
    cr_assert_stdout_eq_str(get_file_content("tests/samples/incantation_server.txt"));
    cr_assert_str_eq(client->buffer, get_file_content("tests/samples/incantation_client.txt"));
    cr_assert_str_eq(player->buffer, get_file_content("tests/samples/incantation_player.txt"));
}
