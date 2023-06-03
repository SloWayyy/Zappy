/*
** EPITECH PROJECT 2023
** Zappy
** File description:
** test_utils.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <stdbool.h>
#include <stdio.h>

#include "args.h"
#include "constants.h"
#include "server.h"

static void redirect_all(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(check_arguments, valid_arguments, .init=cr_redirect_stdout)
{
    char const *argv[] = { "./zappy_server", "-p", "4245", "-x", "10", "-y", "10", "-n", "toto", "tata", "-c", "10", "-f", "10", NULL };
    options_t options;

    cr_assert_eq(check_arguments(14, argv, &options), true);
}

Test(check_arguments, unknown_opt, .init=redirect_all)
{
    options_t options;
    check_arguments(2, (char const *[]){"./zappy_server", "-s"}, &options);
    cr_assert_stderr_eq_str("Error: Unknown option: -s\n");
}

Test(check_arguments, only_team_name, .init=cr_redirect_stdout)
{
    options_t options;
    cr_assert_eq(check_arguments(4, (char const *[]){"./zappy_server", "-n", "tfoto", "tatva"}, &options), true);
}

Test(check_arguments, default_values, .init=cr_redirect_stdout)
{
    options_t options;
    check_arguments(3, (char const *[]){"./zappy_server", "-n", "totoo", "tatata"}, &options);

    cr_assert_eq(options.port, DEFAULT_PORT);
    cr_assert_eq(options.width, DEFAULT_WIDTH);
    cr_assert_eq(options.height, DEFAULT_HEIGHT);
    cr_assert_eq(options.clients, DEFAULT_CLIENTS);
    cr_assert_eq(options.freq, DEFAULT_FREQ);
}

Test(check_arguments, invalid_port, .init=redirect_all)
{
    options_t options;
    cr_assert_eq(check_arguments(5, (char const *[]){"./zappy_server", "-p", "toto", "-n", "toto", "tata", NULL}, &options), false);
}

Test(check_arguments, invalid_map_dimension, .init=redirect_all)
{
    options_t options;
    check_arguments(6, (char const *[]){"./zappy_server", "-x", "10", "-n", "toto", "tata", NULL}, &options);
    cr_assert_stderr_eq_str("Error: Map dimensions are not set\n");
}

Test(port_handler, invalid_port_nbr_arg, .init=redirect_all)
{
    options_t options;
    port_handler(5, (char const *[]){"./zappy_server", "-n", "toto", "tata", "-p"}, &options, 4);
    cr_assert_stderr_eq_str("Error: -p requires an argument\n");
}

Test(port_handler, port_already_set, .init=redirect_all)
{
    options_t options;
    options.port = 2000;
    check_arguments(8, (char const *[]){"./zappy_server", "-n", "toto", "tata", "-p", "2000", "-p", "1500"}, &options);
    cr_assert_stderr_eq_str("Error: Port already set\n");
}

Test(port_handler, port_too_big, .init=cr_redirect_stderr)
{
    options_t options;
    cr_assert_eq(port_handler(6, (char const *[]){"./zappy_server", "-n", "toto", "tata", "-p", "65536"}, &options, 4), -1);
}

Test(check_arguments, no_team_name, .init=redirect_all)
{
    options_t options;
    check_arguments(1, (char const *[]){"./zappy_server"}, &options);
    cr_assert_stderr_eq_str("Error: Team names are not set\n");
}

Test(height_handler, invalid_height_nbr_arg, .init=redirect_all)
{
    options_t options;
    height_handler(5, (char const *[]){"./zappy_server", "-n", "toto", "tata", "-y"}, &options, 4);
    cr_assert_stderr_eq_str("Error: -y requires an argument\n");
}

Test(height_handler, height_already_set, .init=redirect_all)
{
    options_t options;
    options.height = 2000;
    cr_assert_eq(check_arguments(8, (char const *[]){"./zappy_server", "-n", "toto", "tata", "-y", "10", "-y", "15"}, &options), false);
}

Test(check_positive, valid_nbr)
{
    int storage = 0;
    cr_assert_eq(check_positive("10", "-p", &storage), true);
    cr_assert_eq(storage, 10);
}

Test(check_positive, invalid_nbr, .init=cr_redirect_stderr)
{
    int storage = 0;
    cr_assert_eq(check_positive("toto", "-p", &storage), false);
}

Test(check_positive, neg_nbr, .init=cr_redirect_stderr)
{
    int storage = 0;
    cr_assert_eq(check_positive("-10", "-p", &storage), false);
}

Test(width_handler, invalid_width_nbr_arg, .init=redirect_all)
{
    options_t options;
    width_handler(5, (char const *[]){"./zappy_server", "-n", "toto", "tata", "-x"}, &options, 4);
    cr_assert_stderr_eq_str("Error: -x requires an argument\n");
}

Test(width_handler, invalid_value, .init=redirect_all)
{
    options_t options;
    cr_assert_eq(check_arguments(5, (char const *[]){"./zappy_server", "-n", "toto", "tata", "-x", "fdfd"}, &options), false);
}

Test(clients_handler, invalid_clients_nbr_arg, .init=redirect_all)
{
    options_t options;
    clients_handler(5, (char const *[]){"./zappy_server", "-n", "toto", "tata", "-c"}, &options, 4);
    cr_assert_stderr_eq_str("Error: -c requires an argument\n");
}

Test(clients_handler, invalid_value, .init=redirect_all)
{
    options_t options;
    cr_assert_eq(check_arguments(5, (char const *[]){"./zappy_server", "-n", "toto", "tata", "-c", "fdfd"}, &options), false);
}

Test(clients_handler, already_set, .init=redirect_all)
{
    options_t options;
    options.clients = 10;
    clients_handler(8, (char const *[]){"./zappy_server", "-n", "toto", "tata", "-c", "10", "-c", "15"}, &options, 6);
    cr_assert_stderr_eq_str("Error: Clients number already set\n");
}

Test(freq_handler, invalid_freq_nbr_arg, .init=redirect_all)
{
    options_t options;
    freq_handler(5, (char const *[]){"./zappy_server", "-n", "toto", "tata", "-f"}, &options, 4);
    cr_assert_stderr_eq_str("Error: -f requires an argument\n");
}

Test(freq_handler, invalid_value, .init=redirect_all)
{
    options_t options;
    cr_assert_eq(check_arguments(5, (char const *[]){"./zappy_server", "-n", "toto", "tata", "-f", "fdfd"}, &options), false);
}

Test(freq_handler, already_set, .init=redirect_all)
{
    options_t options;
    options.freq = 10;
    freq_handler(8, (char const *[]){"./zappy_server", "-n", "toto", "tata", "-f", "10", "-f", "15"}, &options, 6);
    cr_assert_stderr_eq_str("Error: Frequency already set\n");
}

Test(freq_handler, freq_too_big, .init=redirect_all)
{
    options_t options;
    freq_handler(6, (char const *[]){"./zappy_server", "-n", "toto", "tata", "-f", "200"}, &options, 4);
    cr_assert_stderr_eq_str("Error: Frequency cannot be greater than 100\n");
}

Test(names_handler, invalid_names_nbr_arg, .init=cr_redirect_stderr)
{
    options_t options;
    cr_assert_eq(names_handler(2, (char const *[]){"./zappy_server", "-n"}, &options, 1), -1);
}

Test(names_handler, same_team_name, .init=redirect_all)
{
    options_t options;
    cr_assert_eq(check_arguments(5, (char const *[]){"./zappy_server", "-n", "toto", "tata", "toto"}, &options), false);
}
