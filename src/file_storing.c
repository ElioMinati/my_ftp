/*
** EPITECH PROJECT, 2023
** my_ftp
** File description:
** file_storing
*/

#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "client_actions.h"
#include "string_ops.h"
#include "socket_utils.h"
#include "file_ops.h"

void recieve_client_in_process(client_t *client, const char *dest_file)
{
    fd_set rfds;
    size_t dest_len = 1;
    int tmp_len = 0;
    char *dest = malloc(1 * sizeof(char));
    char *tmp = malloc(2 * sizeof(char));

    dest[0] = '\0';
    FD_ZERO(&rfds);
    FD_SET(client->data_socket, &rfds);
    select(FD_SETSIZE, &rfds, NULL, NULL, NULL);
    while (read(client->data_socket, tmp, 1) > 0) {
        dest_len++;
        dest = get_bigger_dest(dest, dest_len);
        tmp_len = strlen(dest);
        dest[tmp_len] = tmp[0];
        dest[tmp_len + 1] = '\0';
    }
    write_to_file(dest_file, dest);
    free(tmp);
    free(dest);
}

void recieve_file_from_client(server_t *server, int client_socket, char *cmd)
{
    client_t *requested_client = get_client_from_socket(
        server->clients_connected, client_socket);
    char **cmd_stor = my_str_to_word_array(cmd, ' ');
    char *filepath = get_filepath(
        requested_client->working_directory, get_file_name(cmd_stor[1]));
    if (!(is_client_logged_in(server->clients_connected, client_socket)))
        return;
    write(requested_client->client_socket,
        "150 File status okay; about to open data connection\r\n", 53);
    if (connect_to_addr_if_active(server, requested_client, client_socket)
        == -1)
        return;
    if (fork() == 0) {
        recieve_client_in_process(requested_client, filepath);
        write(requested_client->client_socket,
        "226 Closing data connection. File transfer successful\r\n", 55);
        close_data_socket(requested_client, server);
        exit(0);
    }
    requested_client->data_socket_i = NULL;
}

void retrieve_file_send_to_client(client_t *requested_client,
    server_t *server, char **cmd_retr)
{
    char *file_content = read_file(get_filepath(
        requested_client->working_directory, cmd_retr[1]));
    int file_size = get_file_len(get_filepath(
        requested_client->working_directory, cmd_retr[1]));
    if (file_content == NULL || file_size == -1) {
        write(requested_client->client_socket,
            "550 File not found\r\n", 20);
        write(requested_client->client_socket,
            "226 Closing data connection. File aborted\r\n", 43);
        exit(0);
    }
    write_file_to_socket(
        requested_client->data_socket, file_content, file_size);
    write(requested_client->client_socket,
    "226 Closing data connection. File transfer successful\r\n", 55);
    close_data_socket(requested_client, server);
    free(file_content);
    free_arr(cmd_retr);
}

int get_file_len(const char *filepath)
{
    int size = -1;
    struct stat st;

    if (stat(filepath, &st) < 0)
        return size;
    size = st.st_size;
    return size;
}
