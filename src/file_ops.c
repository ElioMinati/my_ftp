/*
** EPITECH PROJECT, 2023
** my_ftp
** File description:
** file_ops
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "server_ftp_main.h"
#include "string_ops.h"
#include "client_actions.h"

char *get_bigger_dest(char *dest, size_t len)
{
    char *new_dest = malloc((len + 1) * sizeof(char));
    new_dest = strcpy(new_dest, dest);
    free(dest);
    return new_dest;
}

char *get_file_name(const char *filepath)
{
    char *filepath_file_ptr = strrchr(filepath, '/');
    char *dest = NULL;

    if (filepath_file_ptr != NULL) {
        dest = malloc(strlen(filepath_file_ptr) * sizeof(char));
        dest = strcpy(dest, filepath_file_ptr + 1);
    } else {
        dest = malloc((strlen(filepath) + 1) * sizeof(char));
        dest = strcpy(dest, filepath);
    }
    return dest;
}

char *read_file(const char *filepath)
{
    size_t len = 1;
    int tmp_len = 0;
    char *dest = malloc(1 * sizeof(char));
    int c;
    FILE *file_ptr = fopen(filepath, "r");

    dest[0] = '\0';
    if (file_ptr == NULL) {
        return NULL;
    }
    while ((c = fgetc(file_ptr)) != EOF) {
        len++;
        dest = get_bigger_dest(dest, len);
        tmp_len = strlen(dest);
        dest[tmp_len] = c;
        dest[tmp_len + 1] = '\0';
    }
    fclose(file_ptr);
    return dest;
}

void write_to_file(const char *filepath, const char *buffer)
{
    FILE *file_ptr = fopen(filepath, "w");

    fprintf(file_ptr, "%s", buffer);
    fclose(file_ptr);
}

void delete_file_on_server(server_t *server, int client_socket, char *cmd)
{
    client_t *requested_client = get_client_from_socket(
        server->clients_connected, client_socket);
    char **cmd_dele = my_str_to_word_array(cmd, ' ');
    char *filepath = get_filepath(requested_client->working_directory,
        cmd_dele[1]);

    if (!(is_client_logged_in(server->clients_connected, client_socket))) {
        write(client_socket, "530 Action refused.\r\n", 21);
        return;
    }
    if (remove(filepath) != 0)
        write(client_socket, "550 Could not delete requested file.\r\n", 38);
    else
        write(client_socket, "250 Requested file action okay, completed.\r\n",
            44);
    free_arr(cmd_dele);
    free(filepath);
}
