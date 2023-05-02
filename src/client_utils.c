/*
** EPITECH PROJECT, 2023
** my_ftp
** File description:
** client_utils
*/

#include <stdlib.h>
#include <string.h>
#include "server_ftp_main.h"
#include "string_ops.h"

int client_len(client_t **clients)
{
    int i = 0;

    for (; clients[i] != NULL; i++);
    return i;
}

client_t *get_client_from_socket(client_t **clients, int socket)
{
    for (int i = 0; clients[i] != NULL; i++) {
        if (clients[i]->client_socket == socket)
            return clients[i];
    }
    return NULL;
}

client_t *get_new_client(int client_socket, struct sockaddr_in sock_addr,
    socklen_t sock_len, char *working_directory)
{
    client_t *new_client = malloc(sizeof(struct client_s));

    new_client->working_directory =
        malloc((strlen(working_directory) + 1) * sizeof(char));
    strcpy(new_client->working_directory, working_directory);
    new_client->data_socket_i = NULL;
    new_client->data_socket = -1;
    new_client->client_socket = client_socket;
    new_client->logged_in = 0;
    new_client->socket_addr = sock_addr;
    new_client->socket_len = sock_len;
    new_client->username = NULL;
    return new_client;
}
