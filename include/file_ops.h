/*
** EPITECH PROJECT, 2023
** my_ftp
** File description:
** file_ops
*/

#include "server_ftp_main.h"

#ifndef FILE_OPS_H_
    #define FILE_OPS_H_

char *read_file(const char *filepath);

void write_to_file(const char *filepath, const char *buffer);

void write_file_to_socket(int socket, char *content, int size);

void retrieve_file_for_client(server_t *server, int client_socket, char *cmd);

void display_help_to_client(int client_socket);

char *get_file_name(const char *filepath);

void delete_file_on_server(server_t *server, int client_socket, char *cmd);

char *get_list_of_dir(char *dirpath);

int get_file_len(const char *filepath);

#endif /* !FILE_OPS_H_ */
