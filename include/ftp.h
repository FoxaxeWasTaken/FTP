/*
** EPITECH PROJECT, 2023
** FTP [WSL : Ubuntu]
** File description:
** ftp
*/

#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <signal.h>

#define MAX_CLIENTS 1024
#define MAX_BUFFER_SIZE 1024

// Server Struct

typedef struct client_s {
    char *address;
    uint16_t port;
    int fd;
    char *username;
    bool is_logged;
    char *path;
    char input_buffer[MAX_BUFFER_SIZE];
} client_t;

typedef struct server_s {
    int fd;
    struct sockaddr_in socket;
    client_t clients[MAX_CLIENTS];
    fd_set readfds;
    char *base_path;
} server_t;

server_t *create_server(int port, char *path);
void delete_server(server_t *server);

// Server Execution

int server_loop(server_t *server);

// Commands

#define NB_COMMANDS 14

typedef struct cmd_s {
    char *name;
    void (*func)(client_t *client, char *args);
} cmd_t;

void handle_commands(client_t *client, char *buffer, int valread);
void exec_noop(client_t *client, char *args);

// Responses

#define NB_RESPONSES 39

typedef struct response_s {
    int code;
    char *message;
} response_t;

void print_response(int fd, int code, char *infos);

// Users

#define NB_USERS 1

typedef struct user_s {
    char *username;
    char *password;
} user_t;

void exec_user(client_t *client, char *args);
void exec_pass(client_t *client, char *args);
void exec_quit(client_t *client, char *args);

// Help

#define NB_HELP 15

typedef struct help_s {
    char *name;
    char *message;
} help_t;

void exec_help(client_t *client, char *args);

// Binary Arguments

void handle_arguments(int argc, char **argv);

// File Transfer

void exec_pasv(client_t *client, char *args);
void exec_port(client_t *client, char *args);
void exec_retr(client_t *client, char *args);
void exec_stor(client_t *client, char *args);

// File Actions

void exec_list(client_t *client, char *args);
void exec_dele(client_t *client, char *args);

// Path Actions

void exec_pwd(client_t *client, char *args);
void exec_cwd(client_t *client, char *args);
void exec_cdup(client_t *client, char *args);

// Handle Signals

int setup_signal(void);

// Errors

// EXIT_SUCCESS is defined in stdlib.h
#define EXIT_ERROR 84

#define NO_ERROR 0
#define ERROR 1
