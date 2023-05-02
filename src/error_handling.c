/*
** EPITECH PROJECT, 2023
** my_ftp
** File description:
** error_handling
*/

#include <stdio.h>
#include <string.h>
#include "string_ops.h"

int handle_help(int ac, char **av)
{
    if (ac == 2 && (strcmp(av[1], "-help") == 0)) {
        printf("USAGE: ./myftp port path\n");
        printf("       port  is the port number on ");
        printf("which the server socket listens\n");
        printf("       path  is the path to the home ");
        printf("directory for the Anonymous user\n");
        return 0;
    }
    return 1;
}

int handle_errors(int ac, char **av)
{
    if (ac != 3) {
        printf("Error: Invalid number of parameters.\n");
        return 84;
    }
    if (is_str_number(av[1]) < 0) {
        printf("Error: Invalid port.\n");
        return 84;
    }
    if (is_path_correct(av[2]) == 0) {
        printf("Error: Invalid path.\n");
        return 84;
    }
    return 0;
}
