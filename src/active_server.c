/*
** EPITECH PROJECT, 2023
** my_ftp
** File description:
** active_server
*/

#include <stdlib.h>
#include <unistd.h>
#include "string_ops.h"
#include "socket_utils.h"
#include "client_actions.h"

int connect_to_addr_if_active(server_t *server, client_t *client,
    int client_socket)
{
    if (client->data_socket_i != NULL &&
        client->data_socket_i->type == ACTIVE) {
        if (connect(client->data_socket,
        (struct sockaddr *)&client->data_socket_i->actv_addr,
        client->data_socket_i->actv_len) == -1) {
            close_data_socket(client, server);
            write(client_socket, "425 Connection failed.\r\n", 24);
            return -1;
        } else {
            return 1;
        }
    }
    return 0;
}

struct sockaddr_in get_client_actv_addr(struct sockaddr_in addr, char *ip_port)
{
    char *ip = get_ip(ip_port);
    int port_wanted = get_port(ip_port);
    struct sockaddr_in new_addr = {
        .sin_addr = inet_addr(ip),
        .sin_family = addr.sin_family,
        .sin_port = htons(port_wanted)
    };

    return new_addr;
}

void open_active_for_client(server_t *server, int client_socket, char *cmd)
{
    client_t *requested_client =
        get_client_from_socket(server->clients_connected, client_socket);
    char **cmd_actv = my_str_to_word_array(cmd, ' ');
    struct sockaddr_in addr;
    socklen_t len;

    if (!is_ip_port_format(cmd_actv[1])) {
        write(client_socket, "501 Wrong format for port.\r\n", 28);
        return;
    }
    requested_client->data_socket_i = get_new_active_data_socket(server);
    requested_client->data_socket_i->actv_addr =
        get_client_actv_addr(requested_client->socket_addr, cmd_actv[1]);
    requested_client->data_socket_i->actv_len =
        sizeof(requested_client->data_socket_i->actv_addr);
    requested_client->data_socket = socket(AF_INET, SOCK_STREAM, 0);
    write(client_socket, "200 Command okay.\r\n", 19);
    free_arr(cmd_actv);
}
