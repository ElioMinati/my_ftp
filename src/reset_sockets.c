/*
** EPITECH PROJECT, 2023
** my_ftp
** File description:
** reset_sockets
*/

#include <stdio.h>
#include "server_ftp_main.h"

void handle_select(server_t *server)
{
    for (int i = 0; i < FD_SETSIZE; i++) {
        if (handle_server_select(i, server))
            break;
    }
}

void reset_file_descriptors(server_t *server)
{
    FD_ZERO(&server->rfds);
    FD_SET(server->server_socket, &server->rfds);
    for (int i = 0; server->clients_connected[i] != NULL; i++) {
        FD_SET(server->clients_connected[i]->client_socket, &server->rfds);
        if (server->clients_connected[i]->data_socket_i != NULL) {
            FD_SET(server->clients_connected[i]->data_socket_i->socket,
                &server->rfds);
        }
    }
}
