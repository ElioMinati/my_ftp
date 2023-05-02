/*
** EPITECH PROJECT, 2023
** my_ftp
** File description:
** passive_server
*/

#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "server_ftp_main.h"
#include "client_actions.h"
#include "socket_utils.h"
#include "string_ops.h"
#include "file_ops.h"

char *get_passive_mode_string(char **ip, in_port_t port)
{
    char *dest = malloc(1040 * sizeof(char));
    int p2 = port % 256;
    int p1 = (port - p2) / 256;
    char strp2[10];
    char strp1[10];

    strcpy(dest, "227 Entering Passive Mode (");
    for (int i = 0; i < 4; i++) {
        dest = strcat(dest, ip[0]);
        dest = strcat(dest, ",");
    }
    sprintf(strp1, "%d", p1);
    sprintf(strp2, "%d", p2);
    dest = strcat(dest, strp1);
    dest = strcat(dest, ",");
    dest = strcat(dest, strp2);
    dest = strcat(dest, ")\r\n");
    return dest;
}

void open_passive_for_client(server_t *server, int client_socket)
{
    char *pasv_mode_str = NULL;
    char **ip = NULL;
    data_socket_t *new_socket = get_new_data_socket(server);
    client_t *requested_client = get_client_from_socket(
        server->clients_connected, client_socket);

    if (!(is_client_logged_in(server->clients_connected, client_socket)))
        return;
    requested_client->data_socket_i = new_socket;
    ip = my_str_to_word_array(
        inet_ntoa(new_socket->socket_addr.sin_addr), '.');
    pasv_mode_str = get_passive_mode_string(ip,
        ntohs(new_socket->socket_addr.sin_port));
    write(client_socket, pasv_mode_str, strlen(pasv_mode_str));
    FD_SET(new_socket->socket, &server->rfds);
    free_arr(ip);
    free(pasv_mode_str);
}

void accept_new_client_on_data(int fds, server_t *server, client_t *client)
{
    (void)server;
    struct sockaddr_in dest;
    socklen_t socklen = sizeof(dest);
    client->data_socket = accept(fds, (struct sockaddr *)&dest, &socklen);
}

void write_file_to_socket(int socket, char *content, int size)
{
    for (int i = 0; i < size; i++) {
        write(socket, &(content[i]), 1);
    }
}

void retrieve_file_for_client(server_t *server, int client_socket, char *cmd)
{
    client_t *requested_client = get_client_from_socket(
        server->clients_connected, client_socket);
    char **cmd_retr = my_str_to_word_array(cmd, ' ');
    if (!(is_client_logged_in(server->clients_connected, client_socket)))
        return;
    if (requested_client->data_socket_i == NULL) {
        write(client_socket, "530 Not authorized.\r\n", 21);
        free_arr(cmd_retr);
        return;
    }
    write(requested_client->client_socket,
    "150 File status okay; about to open data connection\r\n", 53);
    if (connect_to_addr_if_active(server, requested_client, client_socket)
        == -1)
        return;
    if (fork() == 0) {
        retrieve_file_send_to_client(requested_client, server, cmd_retr);
        exit(0);
    }
    requested_client->data_socket_i = NULL;
}
