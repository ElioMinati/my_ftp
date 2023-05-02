/*
** EPITECH PROJECT, 2023
** my_ftp
** File description:
** server_ftp_main
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <netinet/ip.h>
#include <arpa/inet.h>

#ifndef SERVER_FTP_MAIN_H_
    #define SERVER_FTP_MAIN_H_

typedef enum transfer_type_e {
    ACTIVE,
    PASSIVE
} transfer_type;

typedef struct data_socket_s {

    struct sockaddr_in socket_addr;
    socklen_t socket_len;
    struct sockaddr_in actv_addr;
    socklen_t actv_len;
    int socket;
    transfer_type type;

} data_socket_t;

typedef struct client_s {

    struct sockaddr_in socket_addr;
    socklen_t socket_len;
    int client_socket;
    char *username;
    char *working_directory;
    int logged_in;
    data_socket_t *data_socket_i;
    int data_socket;

} client_t;

typedef struct server_s {

    struct sockaddr_in socket_addr;
    socklen_t socket_len;
    int server_socket;
    fd_set rfds;
    client_t **clients_connected;
    char *main_path;

} server_t;

void do_server_loop(server_t *server);

void setup_server(server_t *server_info, int port, char *path);

void accept_new_client_on_data(int fds, server_t *server, client_t *client);

void reset_file_descriptors(server_t *server);

void handle_select(server_t *server);

int handle_server_select(int fds, server_t *server);

#endif /* !SERVER_FTP_MAIN_H_ */
