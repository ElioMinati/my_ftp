/*
** EPITECH PROJECT, 2023
** my_ftp
** File description:
** client_working_directories
*/

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "string_ops.h"
#include "client_actions.h"
#include "server_ftp_main.h"

char *get_combined_working_directory(char *cwd, char *new)
{
    char *dest = NULL;

    if (new == NULL)
        return NULL;
    dest = malloc((strlen(cwd) + strlen(new) + 2) * sizeof(char));
    if (new[0] == '/')
        dest = strcpy(dest, new);
    else {
        dest = strcpy(dest, cwd);
        if (dest[strlen(dest) - 1] != '/') {
            dest = strcat(dest, "/");
            dest = strcat(dest, new);
        }
    }
    return dest;
}

void client_change_working_directory(
    server_t *server, int client_socket, char *cmd)
{
    client_t *requested_client = get_client_from_socket(
        server->clients_connected, client_socket);
    char **cmd_cwd = my_str_to_word_array(cmd, ' ');
    char *requested_path = get_combined_working_directory(
        requested_client->working_directory, cmd_cwd[1]);
    if (!(is_client_logged_in(server->clients_connected, client_socket)))
        return;
    if (requested_path != NULL && is_path_correct(requested_path)) {
        free(requested_client->working_directory);
        requested_client->working_directory = requested_path;
        write(client_socket,
            "250 Requested file action okay, completed.\r\n", 44);
        return;
    } else {
        write(client_socket, "550 Incorrect path.\r\n", 21);
    }
    free_arr(cmd_cwd);
}

void client_up_working_directory(server_t *server, int client_socket)
{
    client_t *requested_client =
        get_client_from_socket(server->clients_connected, client_socket);
    char *up_path = get_up_path(requested_client->working_directory);

    if (!(is_client_logged_in(server->clients_connected, client_socket)))
        return;
    if (up_path != NULL && is_path_correct(up_path)) {
        free(requested_client->working_directory);
        requested_client->working_directory = up_path;
        write(client_socket, "200 Command okay.\r\n", 19);
    } else {
        write(client_socket, "550 Incorrect path.\r\n", 21);
    }
}
