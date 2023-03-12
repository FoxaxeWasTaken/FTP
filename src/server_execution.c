/*
** EPITECH PROJECT, 2023
** FTP [WSL : Ubuntu]
** File description:
** server_execution
*/

#include "ftp.h"

static int reset_fds(server_t *server)
{
    int max_fd = server->fd;

    FD_ZERO(&server->readfds);
    FD_SET(server->fd, &server->readfds);
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (server->clients[i].fd > 0) {
            FD_SET(server->clients[i].fd, &server->readfds);
            max_fd = (server->clients[i].fd > max_fd) ?
                server->clients[i].fd : max_fd;
        }
    }
    return max_fd;
}

static int add_new_client(server_t *server)
{
    struct sockaddr_in new_socket;
    socklen_t socklen = sizeof(new_socket);
    int new_fd = accept(server->fd, (struct sockaddr *)&new_socket, &socklen);

    if (new_fd == -1)
        return ERROR;
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (server->clients[i].fd == 0) {
            server->clients[i].fd = new_fd;
            server->clients[i].address = inet_ntoa(new_socket.sin_addr);
            server->clients[i].port = ntohs(new_socket.sin_port);
            server->clients[i].path = strdup(server->base_path);
            FD_SET(new_fd, &server->readfds);
            break;
        }
    }
    fprintf(stderr, "\033[0;32mLOG: Connection accepted from %s:%d\n\033[0m",
        inet_ntoa(new_socket.sin_addr), ntohs(new_socket.sin_port));
    print_response(new_fd, 220, "");
    return NO_ERROR;
}

static void handle_request(server_t *server)
{
    int valread = 0;
    char buffer[1024] = {0};

    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (FD_ISSET(server->clients[i].fd, &server->readfds)) {
            valread = read(server->clients[i].fd, buffer, 1024);
            handle_commands(&server->clients[i], buffer, valread);
        }
        memset(buffer, 0, 1024);
    }
}

static int handle_activity(server_t *server)
{
    if (FD_ISSET(server->fd, &server->readfds)) {
        if (add_new_client(server) != 0) {
            return ERROR;
        }
    } else {
        handle_request(server);
    }
    return NO_ERROR;
}

int server_loop(server_t *server)
{
    int max_sd = 0;

    if (listen(server->fd, MAX_CLIENTS) == -1)
        return ERROR;
    fprintf(stderr, "\033[42m\033[30mLOG: SERVER STARTED\n\033[0m");
    while (42) {
        max_sd = reset_fds(server);
        if (select(max_sd + 1, &server->readfds, NULL, NULL, NULL) < 1) {
            return ERROR;
        }
        if (handle_activity(server) != 0) {
            return ERROR;
        }
    }
    return NO_ERROR;
}
