/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** test_utils.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "args.h"
#include "constants.h"
#include "server.h"

Test(check_arguments, valid_arguments)
{
    char const *argv[] = { "./zappy_server", "-p", "4245", "-x", "10", "-y", "10", "-n", "toto", "tata", "-c", "10", "-f", "10", NULL };
    options_t options;

    memset(&options, 0, sizeof(options_t));
    cr_assert_eq(check_arguments(14, argv, &options), true);
}

Test(check_arguments, unknown_option, .init=cr_redirect_stderr)
{
    char const *argv[] = { "./zappy_server", "-s" };
    options_t options;

    memset(&options, 0, sizeof(options_t));
    cr_assert_eq(check_arguments(2, argv, &options), false);
    cr_assert_stderr_eq_str("Error: Unknown option: -s\n");
}

Test(check_arguments, only_team_name, .init=cr_redirect_stdout)
{
    char const *argv[] = { "./zappy_server", "-n", "tfoto", "tatva" };
    options_t options;

    memset(&options, 0, sizeof(options_t));
    cr_assert_eq(check_arguments(4, argv, &options), true);
}

Test(check_arguments, default_values, .init=cr_redirect_stdout)
{
    char const *argv[] = { "./zappy_server", "-n", "totoo", "tatata" };
    options_t options;

    memset(&options, 0, sizeof(options_t));
    cr_assert_eq(check_arguments(4, argv, &options), true);
    cr_assert_eq(options.port, DEFAULT_PORT);
    cr_assert_eq(options.width, DEFAULT_WIDTH);
    cr_assert_eq(options.height, DEFAULT_HEIGHT);
    cr_assert_eq(options.clients, DEFAULT_CLIENTS);
    cr_assert_eq(options.freq, DEFAULT_FREQ);
}

Test(check_arguments, invalid_port, .init=cr_redirect_stderr)
{
    char const *argv[] = { "./zappy_server", "-p", "toto", "-n", "toto", "tata" };
    options_t options;

    memset(&options, 0, sizeof(options_t));
    cr_assert_eq(check_arguments(6, argv, &options), false);
    cr_assert_stderr_eq_str("Error: Port must be a number\n");
}

Test(check_arguments, incomplete_map_dimensions, .init=cr_redirect_stderr)
{
    char const *argv[] = { "./zappy_server", "-x", "10", "-n", "toto", "tata" };
    options_t options;

    memset(&options, 0, sizeof(options_t));
    cr_assert_eq(check_arguments(6, argv, &options), false);
    cr_assert_stderr_eq_str("Error: Map dimensions are not set\n");
}

Test(check_arguments, missing_port_argument, .init=cr_redirect_stderr)
{
    char const *argv[] = { "./zappy_server", "-n", "toto", "tata", "-p" };
    options_t options;

    memset(&options, 0, sizeof(options_t));
    cr_assert_eq(check_arguments(5, argv, &options), false);
    cr_assert_stderr_eq_str("Error: -p requires an argument\n");
}

Test(check_arguments, port_already_set, .init=cr_redirect_stderr)
{
    char const *argv[] = { "./zappy_server", "-n", "toto", "tata", "-p", "2000", "-p", "1500" };
    options_t options;

    memset(&options, 0, sizeof(options_t));
    cr_assert_eq(check_arguments(8, argv, &options), false);
    cr_assert_stderr_eq_str("Error: Port already set\n");
}

Test(port_handler, port_too_big, .init=cr_redirect_stderr)
{
    char const *argv[] = { "./zappy_server", "-n", "toto", "tata", "-p", "65536" };
    options_t options;

    memset(&options, 0, sizeof(options_t));
    cr_assert_eq(check_arguments(6, argv, &options), false);
    cr_assert_stderr_eq_str("Error: Port must be between 1 and 65535\n");
}

Test(check_arguments, no_arguments, .init=cr_redirect_stdout)
{
    char const *argv[] = { "./zappy_server" };
    options_t options;

    memset(&options, 0, sizeof(options_t));
    cr_assert_eq(check_arguments(1, argv, &options), true);
}

Test(check_arguments, invalid_height_nbr_arg, .init=cr_redirect_stderr)
{
    char const *argv[] = { "./zappy_server", "-n", "toto", "tata", "-y" };
    options_t options;

    memset(&options, 0, sizeof(options_t));
    cr_assert_eq(check_arguments(5, argv, &options), false);
    cr_assert_stderr_eq_str("Error: -y requires an argument\n");
}

Test(check_arguments, height_already_set, .init=cr_redirect_stderr)
{
    char const *argv[] = { "./zappy_server", "-n", "toto", "tata", "-y", "10", "-y", "15" };
    options_t options;

    memset(&options, 0, sizeof(options_t));
    cr_assert_eq(check_arguments(8, argv, &options), false);
    cr_assert_stderr_eq_str("Error: Height already set\n");
}

Test(check_arguments, invalid_width, .init=cr_redirect_stderr)
{
    char const *argv[] = { "./zappy_server", "-n", "toto", "tata", "-x" };
    options_t options;

    memset(&options, 0, sizeof(options_t));
    cr_assert_eq(check_arguments(5, argv, &options), false);
    cr_assert_stderr_eq_str("Error: -x requires an argument\n");
}

Test(check_arguments, invalid_value, .init=cr_redirect_stderr)
{
    char const *argv[] = { "./zappy_server", "-n", "toto", "tata", "-x", "fdfd" };
    options_t options;

    memset(&options, 0, sizeof(options_t));
    cr_assert_eq(check_arguments(6, argv, &options), false);
    cr_assert_stderr_eq_str("Error: Width must be a number\n");
}

Test(check_arguments, invalid_clients_nbr_arg, .init=cr_redirect_stderr)
{
    char const *argv[] = { "./zappy_server", "-n", "toto", "tata", "-c" };
    options_t options;

    memset(&options, 0, sizeof(options_t));
    cr_assert_eq(check_arguments(5, argv, &options), false);
    cr_assert_stderr_eq_str("Error: -c requires an argument\n");
}

Test(check_arguments, invalid_value_clients, .init=cr_redirect_stderr)
{
    char const *argv[] = { "./zappy_server", "-n", "toto", "tata", "-c", "fdfd" };
    options_t options;

    memset(&options, 0, sizeof(options_t));
    cr_assert_eq(check_arguments(6, argv, &options), false);
    cr_assert_stderr_eq_str("Error: Clients must be a number\n");
}

Test(check_arguments, already_set, .init=cr_redirect_stderr)
{
    char const *argv[] = { "./zappy_server", "-n", "toto", "tata", "-c", "10", "-c", "15" };
    options_t options;

    memset(&options, 0, sizeof(options_t));
    cr_assert_eq(check_arguments(8, argv, &options), false);
    cr_assert_stderr_eq_str("Error: Clients number already set\n");
}

Test(check_arguments, invalid_freq_nbr_arg, .init=cr_redirect_stderr)
{
    char const *argv[] = { "./zappy_server", "-n", "toto", "tata", "-f" };
    options_t options;

    memset(&options, 0, sizeof(options_t));
    cr_assert_eq(check_arguments(5, argv, &options), false);
    cr_assert_stderr_eq_str("Error: -f requires an argument\n");
}

Test(check_arguments, freq_invalid_value, .init=cr_redirect_stderr)
{
    char const *argv[] = {"./zappy_server", "-n", "toto", "tata", "-f", "fdfd" };
    options_t options;

    memset(&options, 0, sizeof(options_t));
    cr_assert_eq(check_arguments(6, argv, &options), false);
    cr_assert_stderr_eq_str("Error: Frequency must be a number\n");
}

Test(check_arguments, freq_already_set, .init=cr_redirect_stderr)
{
    char const *argv[] = { "./zappy_server", "-n", "toto", "tata", "-f", "10", "-f", "15" };
    options_t options;

    memset(&options, 0, sizeof(options_t));
    cr_assert_eq(check_arguments(8, argv, &options), false);
    cr_assert_stderr_eq_str("Error: Frequency already set\n");
}

Test(check_arguments, freq_too_big, .init=cr_redirect_stderr)
{
    char const *argv[] = { "./zappy_server", "-n", "toto", "tata", "-f", "20000" };
    options_t options;

    memset(&options, 0, sizeof(options_t));
    cr_assert_eq(check_arguments(6, argv, &options), false);
    cr_assert_stderr_eq_str("Error: Frequency cannot be greater than 10000\n");
}

Test(check_arguments, invalid_names_argument, .init=cr_redirect_stderr)
{
    char const *argv[] = { "./zappy_server", "-n" };
    options_t options;

    memset(&options, 0, sizeof(options_t));
    cr_assert_eq(check_arguments(2, argv, &options), false);
    cr_assert_stderr_eq_str("Error: No team names given\n");
}

Test(check_arguments, same_team_name, .init=cr_redirect_stderr)
{
    char const *argv[] = { "./zappy_server", "-n", "toto", "tata", "toto" };
    options_t options;

    memset(&options, 0, sizeof(options_t));
    cr_assert_eq(check_arguments(5, argv, &options), false);
    cr_assert_stderr_eq_str("Error: Team toto is registered twice\n");
}
