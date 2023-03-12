/*
** EPITECH PROJECT, 2023
** FTP [WSL : Ubuntu]
** File description:
** server_struct
*/

#include "ftp.h"

static int setup_base_path(server_t *server, char *path)
{
    if (chdir(path) == -1) {
        free(server);
        return ERROR;
    }
    server->base_path = getcwd(NULL, 0);
    return NO_ERROR;
}

static int setup_socket(server_t *server, int port)
{
    server->fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server->fd == -1)
        return ERROR;
    server->socket.sin_family = AF_INET;
    server->socket.sin_port = htons(port);
    server->socket.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(server->fd, (struct sockaddr *)&server->socket,
        sizeof(server->socket)) == -1) {
        free(server);
        return ERROR;
    }
    return NO_ERROR;
}

server_t *create_server(int port, char *path)
{
    server_t *server = malloc(sizeof(server_t));

    if (server == NULL)
        return NULL;
    memset(server->clients, 0, sizeof(client_t) * MAX_CLIENTS);
    if (setup_socket(server, port))
        return NULL;
    if (setup_base_path(server, path))
        return NULL;
    return server;
}

void delete_server(server_t *server)
{
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (server->clients[i].fd != 0)
            close(server->clients[i].fd);
        if (server->clients[i].username != NULL)
            free(server->clients[i].username);
        if (server->clients[i].path != NULL)
            free(server->clients[i].path);
    }
    close(server->fd);
    free(server);
}
