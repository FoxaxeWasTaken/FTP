/*
** EPITECH PROJECT, 2023
** FTP [WSL : Ubuntu]
** File description:
** path_actions
*/

#include "ftp.h"

void exec_pwd(client_t *client, char *args)
{
    if (client->is_logged == false) {
        print_response(client->fd, 530, "");
        return;
    }
    if (args != NULL) {
        print_response(client->fd, 501, "");
        return;
    }
    print_response(client->fd, 257, client->path);
}

void exec_cwd(client_t *client, char *args)
{
    if (client->is_logged == false) {
        print_response(client->fd, 530, "");
        return;
    }
    if (args == NULL) {
        print_response(client->fd, 550, "");
        return;
    }
    if (chdir(args) == -1) {
        print_response(client->fd, 550, "");
        return;
    }
    free(client->path);
    client->path = getcwd(NULL, 0);
    print_response(client->fd, 250, "");
}

void exec_cdup(client_t *client, char *args)
{
    if (client->is_logged == false) {
        print_response(client->fd, 530, "");
        return;
    }
    if (args != NULL) {
        print_response(client->fd, 501, "");
        return;
    }
    if (chdir("..") == -1) {
        print_response(client->fd, 550, "");
        return;
    }
    free(client->path);
    client->path = getcwd(NULL, 0);
    print_response(client->fd, 250, "");
}
