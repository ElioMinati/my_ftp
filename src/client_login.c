/*
** EPITECH PROJECT, 2023
** my_ftp
** File description:
** client_login
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "client_actions.h"
#include "server_ftp_main.h"
#include "string_ops.h"

int is_specific_client_logged_in(client_t *client)
{
    if (!client->logged_in)
        write(client->client_socket, "530 Action refused.\r\n", 21);
    return client->logged_in;
}

int is_client_logged_in(client_t **clients, int client_socket)
{
    for (int i = 0; clients[i] != NULL; i++) {
        if (clients[i]->client_socket == client_socket)
            return is_specific_client_logged_in(clients[i]);
    }
    return 0;
}

void client_log_user(client_t **clients, int client_socket, char *cmd)
{
    client_t *requested_client =
        get_client_from_socket(clients, client_socket);
    char **cmd_user = my_str_to_word_array(cmd, ' ');

    if (cmd_user[1] != NULL && strcmp(cmd_user[1], "Anonymous") == 0) {
        requested_client->username =
            malloc((strlen(cmd_user[1]) + 1) * sizeof(char));
        strcpy(requested_client->username, cmd_user[1]);
        write(client_socket, "331 User name okay, need password.\r\n", 36);
    } else {
        write(client_socket, "331 Account not found.\r\n", 24);
    }
}

void accept_new_client(server_t *server)
{
    int clientlen = client_len(server->clients_connected);
    int new_client = 0;
    struct sockaddr_in dest;
    socklen_t lendest = sizeof(dest);

    new_client = accept(server->server_socket,
        (struct sockaddr *)&dest, &lendest);
    FD_SET(new_client, &server->rfds);
    server->clients_connected = realloc(server->clients_connected,
        (clientlen + 2) * sizeof(struct client_s *));
    server->clients_connected[clientlen] =
        get_new_client(new_client, dest, lendest, server->main_path);
    server->clients_connected[clientlen + 1] = NULL;
    write(new_client, "220 Service ready for new user.\r\n", 33);
}

void client_log_pwd(client_t **clients, int client_socket, char *cmd)
{
    client_t *requested_client =
        get_client_from_socket(clients, client_socket);
    char **cmd_pwd = my_str_to_word_array(cmd, ' ');

    if (cmd_pwd[1] == NULL || cmd_pwd[1][0] == '\0') {
        if (requested_client->username == NULL) {
            write(client_socket, "331 Need account for login.\r\n", 29);
            return;
        } else {
            requested_client->logged_in = 1;
            write(client_socket, "230 User logged in, proceed.\r\n", 30);
        }
    } else
        write(client_socket, "530 Incorrect password.\r\n", 25);
    free_arr(cmd_pwd);
}
