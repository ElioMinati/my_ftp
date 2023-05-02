/*
** EPITECH PROJECT, 2023
** my_ftp
** File description:
** client_help
*/

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "file_ops.h"
#include "client_actions.h"

void display_help_to_client(int client_socket)
{
    char *buffer = read_file("help.txt");

    write(client_socket, buffer, strlen(buffer));
    write(client_socket, "\r\n", 2);
    free(buffer);
}

void display_working_directoy_to_client(server_t *server, int client_socket)
{
    client_t *requested_client =
        get_client_from_socket(server->clients_connected, client_socket);
    char *msg_to_send = malloc((8 +
        strlen(requested_client->working_directory)) * sizeof(char));

    if (!is_client_logged_in(server->clients_connected, client_socket))
        return;
    strcpy(msg_to_send, "257 ");
    msg_to_send = strcat(msg_to_send, requested_client->working_directory);
    msg_to_send = strcat(msg_to_send, ".\r\n");
    write(client_socket, msg_to_send,
        strlen(msg_to_send));
}
