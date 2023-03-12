/*
** EPITECH PROJECT, 2023
** FTP [WSL : Ubuntu]
** File description:
** user
*/

#include "ftp.h"

static const user_t users[NB_USERS] = {
    {"Anonymous", NULL}
};

static int find_user(char *username)
{
    for (int idx = 0; idx < NB_USERS; idx++) {
        if (strcmp(username, users[idx].username) == 0)
            return idx;
    }
    return -1;
}

static bool is_matching(char *username, char *password)
{
    int user_idx = find_user(username);

    if (user_idx == -1)
        return false;
    if (users[user_idx].password == NULL && password == NULL)
        return true;
    if (users[user_idx].password == NULL || password == NULL)
        return false;
    if (strcmp(password, users[user_idx].password) == 0)
        return true;
    return false;
}

void exec_pass(client_t *client, char *args)
{
    if (client->is_logged) {
        print_response(client->fd, 230, "");
        return;
    }
    if (client->username == NULL) {
        print_response(client->fd, 332, "");
        return;
    }
    if (is_matching(client->username, args)) {
        print_response(client->fd, 230, "");
        client->is_logged = true;
        fprintf(stderr, "\033[34mLOG: Client from %s:%d logged in as "
            "%s\n\033[0m", client->address, client->port, client->username);
    } else {
        print_response(client->fd, 530, "");
    }
}

void exec_user(client_t *client, char *args)
{
    if (client->is_logged) {
        print_response(client->fd, 230, "");
        return;
    }
    if (args == NULL) {
        print_response(client->fd, 501, "");
        return;
    }
    if (client->username != NULL)
        free(client->username);
    client->username = strdup(args);
    print_response(client->fd, 331, "");
}

void exec_quit(client_t *client, char *args)
{
    if (args != NULL) {
        print_response(client->fd, 501, "");
        return;
    }
    print_response(client->fd, 221, "");
    close(client->fd);
    client->fd = 0;
    client->is_logged = false;
    free(client->username);
    client->username = NULL;
    free(client->path);
    fprintf(stderr, "\033[31mLOG: Client from %s:%d disconnected\n\033[0m",
        client->address, client->port);
}
