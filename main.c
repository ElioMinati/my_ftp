/*
** EPITECH PROJECT, 2023
** main.c
** File description:
** main for myftp
*/

#include <stdlib.h>
#include "error_handling.h"
#include "server_ftp_main.h"

int main(int ac, char **av)
{
    server_t server_info;

    if (handle_help(ac, av) == 0)
        return 0;
    if (handle_errors(ac, av) == 84)
        return 84;
    setup_server(&server_info, atoi(av[1]), av[2]);
    do_server_loop(&server_info);
    return 0;
}
