/*
** EPITECH PROJECT, 2023
** my_ftp
** File description:
** directory_listing
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "client_actions.h"
#include "server_ftp_main.h"
#include "string_ops.h"
#include "file_ops.h"
#include "socket_utils.h"

static void write_list_to_process(client_t *requested_client,
    server_t *server, char **full_cmd)
{
    char *res = NULL;

    if (full_cmd[1] == NULL || full_cmd[1][0] == '\0')
        res = get_list_of_dir(requested_client->working_directory);
    else
        res = get_list_of_dir(get_filepath(
            requested_client->working_directory, full_cmd[1]));
    write_file_to_socket(requested_client->data_socket, res, strlen(res));
    write(requested_client->client_socket,
        "226 Closing data connection. File transfer successful\r\n", 55);
    close_data_socket(requested_client, server);
    free(res);
    free_arr(full_cmd);
}

void list_directory(server_t *server, int client_socket, char *cmd)
{
    char **full_cmd = my_str_to_word_array(cmd, ' ');
    client_t *requested_client = get_client_from_socket(
        server->clients_connected, client_socket);
    if (!is_client_logged_in(server->clients_connected, client_socket))
        return;
    write(requested_client->client_socket,
        "150 File status okay; about to open data connection\r\n", 53);
    if (requested_client->data_socket_i == NULL) {
        write(requested_client->client_socket,
        "425 No data connection\r\n", 24);
        return;
    }
    if (connect_to_addr_if_active(server,
        requested_client, client_socket) == -1)
        return;
    if (fork() == 0) {
        write_list_to_process(requested_client, server, full_cmd);
        exit(0);
    }
    free_arr(full_cmd);
}
