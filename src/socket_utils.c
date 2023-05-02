/*
** EPITECH PROJECT, 2023
** my_ftp
** File description:
** socket_utils
*/

#include <stdlib.h>
#include <unistd.h>
#include "client_actions.h"

struct sockaddr_in get_address_with_free_port(
    int socket, struct sockaddr_in original, int custom_port)
{
    struct sockaddr_in new_addr = {
        .sin_family = original.sin_family,
        .sin_port = original.sin_port,
        .sin_addr = original.sin_addr
    };
    if (custom_port == -1) {
        while (bind(socket, (struct sockaddr *)&new_addr,
            sizeof(new_addr)) == -1) {
            new_addr.sin_port = htons(ntohs(new_addr.sin_port) + 1);
        }
    } else {
        while (bind(socket, (struct sockaddr *)&new_addr,
            sizeof(new_addr)) == -1) {
            new_addr.sin_port = htons(ntohs(new_addr.sin_port) - 1);
        }
    }
    return new_addr;
}

data_socket_t *get_new_active_data_socket(server_t *server)
{
    data_socket_t *new_socket = malloc(sizeof(data_socket_t));

    new_socket->socket = socket(AF_INET, SOCK_STREAM, 0);
    new_socket->socket_addr = get_address_with_free_port(
        new_socket->socket, server->socket_addr, -1);
    new_socket->socket_len = sizeof(new_socket->socket_addr);
    new_socket->type = ACTIVE;
    return new_socket;
}

data_socket_t *get_new_data_socket(server_t *server)
{
    data_socket_t *new_socket = malloc(sizeof(data_socket_t));

    new_socket->socket = socket(AF_INET, SOCK_STREAM, 0);
    new_socket->socket_addr = get_address_with_free_port(
        new_socket->socket, server->socket_addr, -1);
    new_socket->socket_len = sizeof(new_socket->socket_addr);
    listen(new_socket->socket, 5);
    new_socket->type = PASSIVE;
    return new_socket;
}

client_t *get_client_from_data_socket(server_t *server, int fds)
{
    for (int i = 0; server->clients_connected[i] != NULL; i++) {
        if (server->clients_connected[i]->data_socket_i != NULL &&
            server->clients_connected[i]->data_socket_i->socket == fds)
            return server->clients_connected[i];
    }
    return NULL;
}

void close_data_socket(client_t *client, server_t *server)
{
    FD_CLR(client->data_socket, &server->rfds);
    close(client->data_socket);
    free(client->data_socket_i);
    client->data_socket_i = NULL;
}
