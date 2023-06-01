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

void redirect_all_stdout(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

bool check_arguments(int argc, char const *argv[], options_t *options);
Test(check_arguments, valid_arguments)
{
    options_t options;
    cr_assert_eq(check_arguments(14, (char const *[]){"./zappy_server", "-p", "4245", "-x", "10", "-y", "10", "-n", "toto", "tata", "-c", "10", "-f", "10", NULL}, &options), true);
}

Test(check_arguments, unkow_opt, .init = redirect_all_stdout)
{
    options_t options;
    check_arguments(2, (char const *[]){"./zappy_server", "-s"}, &options);
    cr_assert_stderr_eq_str("Error: Unknown option: -s\n");
}

Test(check_arguments, only_team_name)
{
    options_t options;
    cr_assert_eq(check_arguments(4, (char const *[]){"./zappy_server", "-n", "toto", "tata", "-p", "5555", NULL}, &options), true);
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

Test(check_arguments, invalid_port, .init = redirect_all_stdout)
{
    options_t options;
    cr_assert_eq(check_arguments(5, (char const *[]){"./zappy_server", "-p", "toto", "-n", "toto", "tata", NULL}, &options), false);
}