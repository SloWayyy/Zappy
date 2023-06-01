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

#include "constants.h"
#include "server.h"

static void redirect_all(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(check_arguments, valid_arguments)
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

Test(check_arguments, only_team_name)
{
    options_t options;
    cr_assert_eq(check_arguments(4, (char const *[]){"./zappy_server", "-n", "tfoto", "tatva"}, &options), true);
}

Test(check_arguments, default_values)
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

int port_handler(int argc, char const *argv[], options_t *options, int idx);
Test(port_handler, invalid_port_nbr_arg, .init=redirect_all)
{
    options_t options;
    port_handler(5, (char const *[]){"./zappy_server", "-n", "toto", "tata", "-p"}, &options, 4);
    cr_assert_stderr_eq_str("Error: -p requires an argument\n");
}

Test(port_handler, port_already_set, .init=redirect_all)
{
    options_t options;
    check_arguments(8, (char const *[]){"./zappy_server", "-n", "toto", "tata", "-p", "10", "-p", "15"}, &options);
    cr_assert_stderr_eq_str("Error: Port already set\n");
}

Test(port_handler, port_too_big)
{
    options_t options;
    cr_assert_eq(port_handler(6, (char const *[]){"./zappy_server", "-n", "toto", "tata", "-p", "65536"}, &options, 4), -1);
}


// height_handler a faire
// clients_handler a faire