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
    process_t *process = launch_server(argv);

    usleep(1000000);
    exit_server(process);
    cr_assert_eq(res, 0);
}

Test(server, unknown_client, .timeout = 5, .init=cr_redirect_stdout)
{
    char *argv[] = { "./zappy_server", "-p", "8001", NULL };
    pthread_t thread;
    process_t *process = launch_server(argv);
    routine_t *client = launch_client(&thread, 8001);

    execute_command(client, "test");
    get_output(client);
    exit_server(process);
    exit_client(&thread, client);
    cr_assert_str_eq(client->buffer, "WELCOME\nko\n");
}

Test(server, graphic_client_default, .timeout = 5, .init=cr_redirect_stdout)
{
    char *argv[] = { "./zappy_server", "-p", "8002", NULL };
    pthread_t thread;
    process_t *process = launch_server(argv);
    routine_t *client = launch_client(&thread, 8002);
    buffer_t *buffer = new_buffer();
    char *resource_line = strdup("bct x y");

    cr_assert_not_null(buffer);
    cr_assert_not_null(resource_line);
    execute_command(client, "GRAPHIC");
    get_output(client);
    exit_server(process);
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
    process_t *process = launch_server(argv);
    routine_t *client = launch_client(&thread, 8003);

    execute_command(client, "GRAPHIC");
    get_output(client);
    exit_server(process);
    exit_client(&thread, client);
    fflush(stdout);
    cr_assert_stdout_eq_str(get_file_content("tests/samples/single_tile_server.txt"));
    cr_assert_str_eq(client->buffer, get_file_content("tests/samples/single_tile_client.txt"));
}

Test(server, graphical_tick, .timeout = 5, .init=cr_redirect_stdout)
{
    char *argv[] = { "./zappy_server", "-p", "8004", "-x", "1", "-y", "1", NULL };
    pthread_t thread;
    process_t *process = launch_server(argv);
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
    exit_server(process);
    exit_client(&thread, client);
    cr_assert_str_eq(client->buffer, get_file_content("tests/samples/tick_client.txt"));
}

Test(server, graphical_infos, .timeout = 5, .init=cr_redirect_stdout)
{
    char *argv[] = { "./zappy_server", "-p", "8005", "-x", "1", "-y", "1", NULL };
    pthread_t thread;
    process_t *process = launch_server(argv);
    routine_t *client = launch_client(&thread, 8005);

    execute_command(client, "GRAPHIC");
    execute_command(client, "abc");
    execute_command(client, "msz");
    execute_command(client, "msz aaa");
    execute_command(client, "bct 0 0");
    get_output(client);
    exit_server(process);
    exit_client(&thread, client);
    cr_assert_str_eq(client->buffer, get_file_content("tests/samples/infos_client.txt"));
}

Test(server, player_connection, .timeout = 5, .init=cr_redirect_stdout)
{
    char *argv[] = { "./zappy_server", "-p", "8006", "-x", "1", "-y", "1", NULL };
    pthread_t thread;
    pthread_t thread_player;
    process_t *process = launch_server(argv);
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
    exit_server(process);
    exit_client(&thread, client);
    exit_client(&thread, player);
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
    process_t *process = launch_server(argv);
    routine_t *client = launch_client(&thread, 8007);
    routine_t *player = launch_client(&thread_player, 8007);

    execute_command(client, "GRAPHIC");
    execute_command(player, "Team1");
    get_output(client);
    get_output(player);
    usleep(500000);
    get_output(client);
    get_output(player);
    exit_server(process);
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
    process_t *process = launch_server(argv);
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
    exit_server(process);
    exit_client(&thread, client);
    exit_client(&thread, player);
    fflush(stdout);
    cr_assert_stdout_eq_str(get_file_content("tests/samples/incantation_server.txt"));
    cr_assert_str_eq(client->buffer, get_file_content("tests/samples/incantation_client.txt"));
    cr_assert_str_eq(player->buffer, get_file_content("tests/samples/incantation_player.txt"));
}

Test(server, server_commands_help, .timeout = 5, .init=cr_redirect_stdout)
{
    char *argv[] = { "./zappy_server", "-p", "8009", "--debug", NULL };
    process_t *process = launch_server(argv);

    execute_server_command(process, "/kzejkzje");
    execute_server_command(process, "/help");
    execute_server_command(process, "/debug");
    exit_server(process);
}

Test(server, kill_refill, .timeout = 5, .init=cr_redirect_stdout)
{
    char *argv[] = { "./zappy_server", "-p", "8010", "--seed", "1234", "-f", "1000", NULL };
    pthread_t thread;
    process_t *process = launch_server(argv);
    routine_t *client = launch_client(&thread, 8010);

    execute_command(client, "GRAPHIC");
    execute_server_command(process, "/debug");
    execute_server_command(process, "/kill @e");
    get_output(client);
    exit_server(process);
    exit_client(&thread, client);
    fflush(stdout);
    cr_assert_stdout_eq_str(get_file_content("tests/samples/kill_refill_server.txt"));
    cr_assert_str_eq(client->buffer, get_file_content("tests/samples/kill_refill_client.txt"));
}

Test(server, pause_resume, .timeout = 10, .init=cr_redirect_stdout)
{
    char *argv[] = { "./zappy_server", "-p", "8011", "--seed", "999", "-f", "1000", "--immortal", NULL };
    char *first = NULL;
    pthread_t thread;
    pthread_t player_thread;
    process_t *process = launch_server(argv);
    routine_t *client = launch_client(&thread, 8011);
    routine_t *player = launch_client(&player_thread, 8011);

    execute_server_command(process, "/resume");
    execute_command(player, "Team1");
    execute_command(client, "GRAPHIC");
    execute_server_command(process, "/pause");
    execute_server_command(process, "/pause");
    execute_command(player, "Forward");
    get_output(player);
    first = strdup(player->buffer);
    execute_server_command(process, "/resume");
    get_output(client);
    get_output(player);
    exit_server(process);
    exit_client(&thread, client);
    exit_client(&player_thread, player);
    fflush(stdout);
    cr_assert_stdout_eq_str(get_file_content("tests/samples/pause_resume_server.txt"));
    cr_assert_str_eq(client->buffer, get_file_content("tests/samples/pause_resume_client.txt"));
    cr_assert_str_eq(first, "WELCOME\n3\n10 10\n");
    cr_assert_str_eq(player->buffer, "ok\n");
}

Test(server, broadcast_teleport, .timeout = 10, .init=cr_redirect_stdout)
{
    char *argv[] = { "./zappy_server", "-p", "8012", "--seed", "25565", "-f", "1000", "--immortal", NULL };
    pthread_t player_thread;
    pthread_t player_thread_2;
    process_t *process = launch_server(argv);
    routine_t *player = launch_client(&player_thread, 8012);
    routine_t *player_2 = launch_client(&player_thread_2, 8012);

    execute_command(player, "Team1");
    execute_command(player_2, "Team1");
    execute_server_command(process, "/tp @r 5 5");
    execute_command(player_2, "Broadcast random");
    usleep(100000);
    execute_server_command(process, "/tp @a 0");
    execute_command(player_2, "Broadcast same zone");
    usleep(100000);
    execute_server_command(process, "/tp 1 ~ ~");
    execute_command(player_2, "Broadcast still same zone");
    usleep(100000);
    execute_server_command(process, "/tp 1 ~ ~-1");
    execute_command(player_2, "Broadcast ahead");
    execute_command(player_2, "Left\nForward");
    execute_command(player_2, "Broadcast ahead left");
    usleep(100000);
    execute_server_command(process, "/tp 1 ~2 ~2");
    execute_command(player_2, "Broadcast behind right");
    usleep(100000);
    get_output(player);
    exit_server(process);
    exit_client(&player_thread, player);
    exit_client(&player_thread_2, player_2);
    fflush(stdout);
    cr_assert_stdout_eq_str(get_file_content("tests/samples/broadcast_teleport_server.txt"));
    cr_assert_str_eq(player->buffer, get_file_content("tests/samples/broadcast_teleport_player.txt"));
}

Test(server, inventory_give, .timeout = 10, .init=cr_redirect_stdout)
{
    char *argv[] = { "./zappy_server", "-p", "8013", "--seed", "666", "-f", "1000", "--immortal", NULL };
    pthread_t thread;
    pthread_t player_thread;
    pthread_t player_thread_2;
    process_t *process = launch_server(argv);
    routine_t *client = launch_client(&thread, 8013);
    routine_t *player = launch_client(&player_thread, 8013);
    routine_t *player_2 = launch_client(&player_thread_2, 8013);

    execute_command(client, "GRAPHIC");
    execute_command(player, "Team1");
    execute_command(player_2, "Team1");
    execute_server_command(process, "/give @a linemate 2");
    execute_server_command(process, "/give 1 food");
    execute_command(client, "pin 0");
    execute_command(client, "pin 2");
    execute_command(client, "pin 0 b");
    execute_command(client, "pin 0b b");
    execute_command(client, "pin 0b");
    get_output(client);
    exit_server(process);
    exit_client(&thread, client);
    exit_client(&player_thread, player);
    exit_client(&player_thread_2, player_2);
    fflush(stdout);
    cr_assert_stdout_eq_str(get_file_content("tests/samples/inventory_give_server.txt"));
    cr_assert_str_eq(client->buffer, get_file_content("tests/samples/inventory_give_client.txt"));
}

Test(server, look_take_set, .timeout = 10, .init=cr_redirect_stdout)
{
    char *argv[] = { "./zappy_server", "-p", "8014", "--seed", "12345", "-f", "1000", "--immortal", "--debug", NULL };
    pthread_t thread;
    pthread_t player_thread;
    process_t *process = launch_server(argv);
    routine_t *client = launch_client(&thread, 8014);
    routine_t *player = launch_client(&player_thread, 8014);

    execute_command(client, "GRAPHIC");
    execute_command(player, "Team1");
    execute_server_command(process, "/tp @a 5 8");
    execute_command(player, "Look");
    execute_command(player, "Take linemate");
    execute_command(player, "Take linemate");
    execute_command(player, "Take lainemet");
    execute_command(player, "Take");
    execute_command(player, "Inventory");
    execute_command(player, "Set linemate");
    execute_command(player, "Set linemate");
    execute_command(player, "Set lainemet");
    execute_command(player, "Set");
    execute_command(player, "Look");
    usleep(100000);
    execute_server_command(process, "/tp @e 3 3");
    execute_command(player, "Look");
    execute_command(player, "Right");
    execute_command(player, "Look");
    usleep(100000);
    execute_server_command(process, "/kill @a");
    get_output(client);
    get_output(player);
    exit_server(process);
    exit_client(&thread, client);
    exit_client(&player_thread, player);
    fflush(stdout);
    cr_assert_stdout_eq_str(get_file_content("tests/samples/look_take_set_server.txt"));
    cr_assert_str_eq(client->buffer, get_file_content("tests/samples/look_take_set_client.txt"));
    cr_assert_str_eq(player->buffer, get_file_content("tests/samples/look_take_set_player.txt"));
}

Test(server, fork_eject, .timeout = 10, .init=cr_redirect_stdout)
{
    char *argv[] = { "./zappy_server", "-p", "8015", "--seed", "7", "-f", "5000", "-c", "1", "--immortal", NULL };
    pthread_t thread;
    pthread_t player_thread;
    pthread_t player_thread_2;
    process_t *process = launch_server(argv);
    routine_t *client = launch_client(&thread, 8015);
    routine_t *player = launch_client(&player_thread, 8015);
    routine_t *player_2 = launch_client(&player_thread_2, 8015);

    execute_command(client, "GRAPHIC");
    execute_command(player, "Team1");
    execute_command(player_2, "Team1");
    execute_command(player, "Connect_nbr");
    execute_command(player, "Fork");
    execute_command(player, "Connect_nbr");
    execute_command(player, "Fork");
    execute_command(player, "Connect_nbr");
    execute_command(player_2, "Team1");
    execute_command(player_2, "Team1");
    execute_command(player_2, "Eject");
    execute_command(player_2, "Eject");
    execute_command(player, "Fork");
    execute_command(player_2, "Eject");
    execute_command(player_2, "Connect_nbr");
    get_output(client);
    get_output(player);
    get_output(player_2);
    exit_server(process);
    exit_client(&thread, client);
    exit_client(&player_thread, player);
    exit_client(&player_thread_2, player_2);
    cr_assert_str_eq(client->buffer, get_file_content("tests/samples/fork_eject_client.txt"));
    cr_assert_str_eq(player->buffer, get_file_content("tests/samples/fork_eject_player.txt"));
    cr_assert_str_eq(player_2->buffer, get_file_content("tests/samples/fork_eject_player_2.txt"));
}

Test(server, graphical_commands_error_handling, .timeout = 5, .init=cr_redirect_stdout)
{
    char *argv[] = { "./zappy_server", "-p", "8016", "-f", "1000","--seed", "25", "--immortal", NULL };
    pthread_t thread;
    pthread_t player_thread;
    process_t *process = launch_server(argv);
    routine_t *client = launch_client(&thread, 8016);
    routine_t *player = launch_client(&player_thread, 8016);

    execute_command(player, "Team1");
    execute_command(player, "Fork");
    usleep(100000);
    execute_command(client, "GRAPHIC");
    execute_command(client, "bct");
    execute_command(client, "bct 0");
    execute_command(client, "bct 0 -1");
    execute_command(client, "bct -1 0");
    execute_command(client, "bct 2 19");
    execute_command(client, "bct 20 1");
    execute_command(client, "bct 20 12");
    execute_command(client, "bct 20a 12");
    execute_command(client, "bct 20 12a");
    execute_command(client, "bct 20a 12a");
    execute_command(client, "bct 20 12 a");
    execute_command(client, "mct 20 12");
    execute_command(client, "mct");
    execute_command(client, "tna");
    execute_command(client, "tna 2");
    execute_command(client, "plv");
    execute_command(client, "plv 1 2");
    execute_command(client, "plv 0");
    execute_command(client, "plv 1");
    execute_command(client, "plv 0a");
    execute_command(client, "ppo");
    execute_command(client, "ppo 1 2");
    execute_command(client, "ppo 0");
    execute_command(client, "ppo 1");
    execute_command(client, "ppo 0a");
    get_output(client);
    exit_server(process);
    exit_client(&thread, client);
    exit_client(&player_thread, player);
    cr_assert_str_eq(client->buffer, get_file_content("tests/samples/graphical_commands_error_handling_client.txt"));
}

Test(server, command_queue, .timeout = 5, .init=cr_redirect_stdout)
{
    char *argv[] = { "./zappy_server", "-p", "8017", "-f", "1000","--seed", "50", "--immortal", NULL };
    pthread_t player_thread;
    process_t *process = launch_server(argv);
    routine_t *player = launch_client(&player_thread, 8017);

    execute_command(player, "Team1");
    execute_command(player, "Forward");
    usleep(50000);
    execute_server_command(process, "/pause");
    execute_command(player, "Forward\nLeft\nRight");
    execute_command(player, "orward\nForward\nForward");
    execute_command(player, "Forward\nForward\nForward");
    execute_command(player, "Yo\nForward\nForward");
    execute_command(player, "Forward\nForward\nForward");
    execute_command(player, "Forward\nForward\nForward");
    execute_server_command(process, "/resume");
    usleep(50000);
    get_output(player);
    exit_server(process);
    exit_client(&player_thread, player);
    cr_assert_str_eq(player->buffer, get_file_content("tests/samples/command_queue_player.txt"));
}

Test(server, incantation_multiple, .timeout = 10, .init=cr_redirect_stdout)
{
    char *argv[] = { "./zappy_server", "-p", "8018", "--seed", "98765", "-f", "5000", "--immortal", "--debug",NULL };
    pthread_t player_thread;
    pthread_t player_thread_2;
    pthread_t player_thread_3;
    process_t *process = launch_server(argv);
    routine_t *player = launch_client(&player_thread, 8018);
    routine_t *player_2 = launch_client(&player_thread_2, 8018);
    routine_t *player_3 = launch_client(&player_thread_3, 8018);

    execute_command(player, "Team1");
    execute_command(player_2, "Team1");
    execute_command(player_3, "Team2");
    execute_server_command(process, "/tp @e 5 5");
    execute_command(player, "Incantation");
    execute_command(player_2, "Incantation");
    execute_command(player_3, "Incantation");
    usleep(200000);
    execute_command(player_3, "Incantation");
    usleep(200000);
    execute_command(player_3, "Incantation");
    usleep(10000);
    execute_server_command(process, "/tp @a 2 3");
    usleep(200000);
    exit_server(process);
    exit_client(&player_thread, player);
    exit_client(&player_thread_2, player_2);
    exit_client(&player_thread_3, player_3);
    fflush(stdout);
    cr_assert_stdout_eq_str(get_file_content("tests/samples/incantation_multiple_server.txt"));
}

Test(server, empty_lines, .timeout = 5, .init=cr_redirect_stdout)
{
    char *argv[] = { "./zappy_server", "-p", "8019", NULL };
    pthread_t thread;
    pthread_t player_thread;
    process_t *process = launch_server(argv);
    routine_t *client = launch_client(&thread, 8019);
    routine_t *player = launch_client(&player_thread, 8019);

    execute_command(client, "\nGRAPHIC");
    execute_command(player, "\nTeam1\n");
    exit_server(process);
    exit_client(&thread, client);
    exit_client(&player_thread, player);
}

Test(server, empty_team_name, .timeout = 5, .init=cr_redirect_stdout)
{
    char *argv[] = { "./zappy_server", "-p", "8020", "-n", "", "--immortal", NULL };
    pthread_t player_thread;
    process_t *process = launch_server(argv);
    routine_t *player = launch_client(&player_thread, 8020);

    execute_command(player, "\n\n");
    get_output(player);
    exit_server(process);
    exit_client(&player_thread, player);
    cr_assert_str_eq(player->buffer, "WELCOME\n3\n10 10\n");
}
