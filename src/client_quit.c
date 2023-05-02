/*
** EPITECH PROJECT, 2023
** my_ftp
** File description:
** client_quit
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <string.h>
#include "client_actions.h"
#include "socket_utils.h"
#include "server_ftp_main.h"

void free_client(client_t *client, server_t *server)
{
    if (client->data_socket_i != NULL)
        close_data_socket(client, server);
    if (client->username != NULL)
        free(client->username);
    if (client->working_directory != NULL)
        free(client->working_directory);
    free(client);
}

void client_quit(int client_socket, server_t *server)
{
    int current_c = 0;

    write(client_socket, "221 Service closing control connection.\r\n", 41);
    for (int i = 0; server->clients_connected[i] != NULL; i++, current_c++) {
        if (server->clients_connected[i]->client_socket == client_socket) {
            free_client(server->clients_connected[i], server);
            current_c++;
        }
        server->clients_connected[i] = server->clients_connected[current_c];
    }
    server->clients_connected = realloc(server->clients_connected,
        client_len(server->clients_connected) + 1);
    FD_CLR(client_socket, &server->rfds);
}

void client_kill(int client_socket, server_t *server)
{
    int current_c = 0;
    int i = 0;
    int current_len = client_len(server->clients_connected);

    for (; server->clients_connected[i] != NULL; i++, current_c++) {
        if (server->clients_connected[i]->client_socket == client_socket) {
            free_client(server->clients_connected[i], server);
            current_c++;
        }
        server->clients_connected[i] = server->clients_connected[current_c];
    }
    server->clients_connected[current_len - 1] = NULL;
    server->clients_connected = realloc(
        server->clients_connected, current_len * sizeof(struct client_s *));
    server->clients_connected[current_len - 1] = NULL;
    FD_CLR(client_socket, &server->rfds);
}
