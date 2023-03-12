/*
** EPITECH PROJECT, 2023
** FTP [WSL : Ubuntu]
** File description:
** file_actions
*/

#include "ftp.h"

void exec_dele(client_t *client, char *args)
{
    if (client->is_logged == false) {
        print_response(client->fd, 530, "");
        return;
    }
    if (args == NULL) {
        print_response(client->fd, 501, "");
        return;
    }
    if (remove(args) == -1) {
        print_response(client->fd, 550, "");
        return;
    }
    print_response(client->fd, 250, "");
}

void exec_list(client_t *client, char *args)
{
    (void)args;
    if (client->is_logged == false) {
        print_response(client->fd, 530, "");
        return;
    }
    print_response(client->fd, 502, "");
}
