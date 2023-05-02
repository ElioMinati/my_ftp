/*
** EPITECH PROJECT, 2023
** my_ftp
** File description:
** socket_utils
*/

#include "server_ftp_main.h"

#ifndef SOCKET_UTILS_H_
    #define SOCKET_UTILS_H_

data_socket_t *get_new_data_socket(server_t *server);

client_t *get_client_from_data_socket(server_t *server, int fds);

struct sockaddr_in get_address_with_free_port(
    int socket, struct sockaddr_in original);

void close_data_socket(client_t *client, server_t *server);

data_socket_t *get_new_active_data_socket(server_t *server);

int connect_to_addr_if_active(server_t *server, client_t *client,
    int client_socket);

#endif /* !SOCKET_UTILS_H_ */
