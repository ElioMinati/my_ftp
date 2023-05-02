/*
** EPITECH PROJECT, 2023
** my_ftp
** File description:
** client_command_parser
*/

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "client_actions.h"
#include "file_ops.h"

static int handle_file_ops(
    int client_socket, server_t *server, char *cmd)
{
    if (!(is_client_logged_in(server->clients_connected, client_socket)))
        return 1;
    if (strncmp(cmd, "RETR", 4) == 0) {
        retrieve_file_for_client(server, client_socket, cmd);
        return 1;
    }
    if (strncmp(cmd, "STOR", 4) == 0) {
        recieve_file_from_client(server, client_socket, cmd);
        return 1;
    }
    if (strncmp(cmd, "DELE", 4) == 0) {
        delete_file_on_server(server, client_socket, cmd);
        return 1;
    }
    if (strncmp(cmd, "CDUP", 4) == 0) {
        client_up_working_directory(server, client_socket);
        return 1;
    }
    return 0;
}

static int handle_file_action_commands(
    int client_socket, server_t *server, char *cmd)
{
    if (!(is_client_logged_in(server->clients_connected, client_socket)))
        return 1;
    if (strncmp(cmd, "PASV", 4) == 0) {
        open_passive_for_client(server, client_socket);
        return 1;
    }
    if (strncmp(cmd, "PORT", 4) == 0) {
        open_active_for_client(server, client_socket, cmd);
        return 1;
    }
    if (strncmp(cmd, "CWD", 3) == 0) {
        client_change_working_directory(server, client_socket, cmd);
        return 1;
    }
    if (strncmp(cmd, "LIST", 4) == 0) {
        list_directory(server, client_socket, cmd);
        return 1;
    }
    return handle_file_ops(client_socket, server, cmd);
}

static int handle_misc_commands(int client_socket, char *cmd)
{
    if (strncmp(cmd, "NOOP", 4) == 0) {
        write(client_socket, "200 Command okay.\r\n", 19);
        return 1;
    }
    if (strncmp(cmd, "HELP", 4) == 0) {
        display_help_to_client(client_socket);
        return 1;
    }
    return 0;
}

void parse_client_command(int client_socket, server_t *server, char *cmd)
{
    if (strncmp(cmd, "USER", 4) == 0) {
        client_log_user(server->clients_connected, client_socket, cmd);
        return;
    }
    if (strncmp(cmd, "PASS", 4) == 0) {
        client_log_pwd(server->clients_connected, client_socket, cmd);
        return;
    }
    if (strncmp(cmd, "QUIT", 4) == 0) {
        client_quit(client_socket, server);
        return;
    }
    if (strncmp(cmd, "PWD", 3) == 0) {
        display_working_directoy_to_client(server, client_socket);
        return;
    }
    if (handle_misc_commands(client_socket, cmd) ||
        handle_file_action_commands(client_socket, server, cmd))
        return;
    write(client_socket, "500 Invalid command.\r\n", 22);
}
