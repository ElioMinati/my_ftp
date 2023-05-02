/*
** EPITECH PROJECT, 2023
** my_ftp
** File description:
** server_main_thread
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
#include "server_ftp_main.h"
#include "socket_utils.h"
#include "string_ops.h"

void setup_server(server_t *server_info, int port, char *path)
{
    int tcp_socket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in a = {
        .sin_family = AF_INET,
        .sin_port = htons(port),
        .sin_addr = INADDR_ANY
    };

    server_info->socket_addr = a;
    server_info->socket_len = sizeof(a);
    server_info->server_socket = tcp_socket;
    server_info->main_path = malloc((strlen(path) + 1) * sizeof(char));
    strcpy(server_info->main_path, path);
    bind(tcp_socket, (struct sockaddr *)&a, sizeof(a));
    listen(tcp_socket, 150);
    FD_ZERO(&server_info->rfds);
    FD_SET(tcp_socket, &server_info->rfds);
    server_info->clients_connected = malloc(1 * sizeof(struct client_s *));
    server_info->clients_connected[0] = NULL;
}

static void handle_action_for_client(int client_socket, server_t *server)
{
    char *dest = malloc(1024 * sizeof(char));

    if (read(client_socket, dest, 1024) < 1) {
        client_kill(client_socket, server);
    } else {
        parse_client_command(client_socket, server, dest);
    }
    free(dest);
}

int handle_server_select(int fds, server_t *server)
{
    if (FD_ISSET(fds, &server->rfds) && fds == server->server_socket) {
        accept_new_client(server);
        return 1;
    }
    if (FD_ISSET(fds, &server->rfds)
        && (get_client_from_data_socket(server, fds) != NULL)) {
        accept_new_client_on_data(fds, server,
            get_client_from_data_socket(server, fds));
        return 1;
    }
    if (FD_ISSET(fds, &server->rfds)) {
        handle_action_for_client(fds, server);
        return 1;
    }
    return 0;
}

static void destroy_server(server_t *server)
{
    for (;server->clients_connected[0] != NULL;)
        client_kill(server->clients_connected[0]->client_socket, server);
    free(server->clients_connected);
    free(server->main_path);
    free(server);
}

void do_server_loop(server_t *server)
{
    while (1) {
        select(FD_SETSIZE, &server->rfds, NULL, NULL, NULL);
        handle_select(server);
        reset_file_descriptors(server);
    }
    destroy_server(server);
}
