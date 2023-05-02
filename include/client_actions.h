/*
** EPITECH PROJECT, 2023
** my_ftp
** File description:
** client_actions
*/

#include "server_ftp_main.h"

#ifndef CLIENT_ACTIONS_H_
    #define CLIENT_ACTIONS_H_

int client_len(client_t **clients);

client_t *get_client_from_socket(client_t **clients, int socket);

client_t *get_new_client(int client_socket, struct sockaddr_in sock_addr,
    socklen_t sock_len, char *working_directory);

void client_quit(int client_socket, server_t *server);

void client_kill(int client_socket, server_t *server);

int is_specific_client_logged_in(client_t *client);

int is_client_logged_in(client_t **client, int client_socket);

void client_log_user(client_t **clients, int client_socket, char *cmd);

void client_log_pwd(client_t **clients, int client_socket, char *cmd);

void parse_client_command(int client_socket, server_t *server, char *cmd);

void free_client(client_t *client, server_t *server);

void open_passive_for_client(server_t *server, int client_socket);

void open_active_for_client(server_t *server, int client_socket, char *cmd);

void display_working_directoy_to_client(server_t *server, int client_socket);

void client_change_working_directory(
    server_t *server, int client_socket, char *cmd);

void client_up_working_directory(server_t *server, int client_socket);

void recieve_file_from_client(server_t *server, int client_socket, char *cmd);

void accept_new_client(server_t *server);

void retrieve_file_send_to_client(client_t *requested_client,
    server_t *server, char **cmd_retr);

void list_directory(server_t *server, int client_socket, char *cmd);

#endif /* !CLIENT_ACTIONS_H_ */
