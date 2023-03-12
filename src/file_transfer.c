/*
** EPITECH PROJECT, 2023
** FTP [WSL : Ubuntu]
** File description:
** file_transfer
*/

#include "ftp.h"

void exec_pasv(client_t *client, char *args)
{
    if (client->is_logged == false) {
        print_response(client->fd, 530, "");
        return;
    }
    if (args != NULL) {
        print_response(client->fd, 501, "");
        return;
    }
    print_response(client->fd, 502, "");
}

void exec_port(client_t *client, char *args)
{
    if (client->is_logged == false) {
        print_response(client->fd, 530, "");
        return;
    }
    if (args == NULL) {
        print_response(client->fd, 501, "");
        return;
    }
    print_response(client->fd, 502, "");
}

void exec_retr(client_t *client, char *args)
{
    if (client->is_logged == false) {
        print_response(client->fd, 530, "");
        return;
    }
    if (args == NULL) {
        print_response(client->fd, 501, "");
        return;
    }
    print_response(client->fd, 502, "");
}

void exec_stor(client_t *client, char *args)
{
    if (client->is_logged == false) {
        print_response(client->fd, 530, "");
        return;
    }
    if (args == NULL) {
        print_response(client->fd, 501, "");
        return;
    }
    print_response(client->fd, 502, "");
}
