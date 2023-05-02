/*
** EPITECH PROJECT, 2023
** my_ftp
** File description:
** port_utils
*/

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "server_ftp_main.h"
#include "socket_utils.h"

int is_ip_port_format(char *ip_port)
{
    int comma_counter = 0;
    int nb_chars = 0;

    for (int i = 0; ip_port[i] != '\0'; i++) {
        if (ip_port[i] == ',') {
            comma_counter++;
            continue;
        }
        if (ip_port[i] < '0' || ip_port[i] > '9')
            nb_chars++;
    }
    if (comma_counter != 5 || nb_chars > 0)
        return 0;
    return 1;
}

char *get_ip(char *buffer)
{
    int counter = 0;
    char *cpy = malloc((strlen(buffer) + 1) * sizeof(char));

    cpy = strcpy(cpy, buffer);
    for (int i = 0; cpy[i] != '\0'; i++) {
        if (counter == 4) {
            cpy[i - 1] = '\0';
            break;
        }
        if (cpy[i] == ',') {
            cpy[i] = '.';
            counter++;
        }
    }
    return cpy;
}

char *get_next_number(char **buffer)
{
    int i = 0;
    char *nb = malloc((strlen(*buffer) + 1) * sizeof(char));

    for (; (*buffer)[0] >= '0' && (*buffer)[0] <= '9'; (*buffer)++) {
        nb[i] = (*buffer)[0];
        i++;
    }
    nb[i] = '\0';
    return nb;
}

int get_port(char *buffer)
{
    int counter = 0;
    int port1 = 0;
    int port2 = 0;
    char *cpy = malloc((strlen(buffer) + 1) * sizeof(char));

    cpy = strcpy(cpy, buffer);
    for (; cpy[0] != '\0'; cpy++) {
        if (counter == 4) {
            port1 = atoi(get_next_number(&cpy));
            cpy++;
            port2 = atoi(get_next_number(&cpy));
            break;
        }
        if (cpy[0] == ',') {
            counter++;
        }
    }
    return (port1 * 256) + port2;
}
