/*
** EPITECH PROJECT, 2023
** FTP [WSL : Ubuntu]
** File description:
** commands
*/

#include "ftp.h"

static const cmd_t commands[NB_COMMANDS] = {
    {"USER", &exec_user},
    {"PASS", &exec_pass},
    {"QUIT", &exec_quit},
    {"PWD", &exec_pwd},
    {"CWD", &exec_cwd},
    {"CDUP", &exec_cdup},
    {"NOOP", &exec_noop},
    {"HELP", &exec_help},
    {"DELE", &exec_dele},
    {"PASV", &exec_pasv},
    {"PORT", &exec_port},
    {"RETR", &exec_retr},
    {"STOR", &exec_stor},
    {"LIST", &exec_list}
};

static const char *unwanted_chars = " \t\r\n";

void exec_noop(client_t *client, char *args)
{
    if (args != NULL) {
        print_response(client->fd, 501, "");
        return;
    }
    print_response(client->fd, 200, "");
}

static bool has_left(client_t *client, int valread)
{
    if (valread == 0) {
        exec_quit(client, NULL);
        return true;
    }
    return false;
}

static bool has_command(client_t *client, char *command)
{
    if (command == NULL) {
        print_response(client->fd, 500, "");
        return false;
    }
    return true;
}

void handle_commands(client_t *client, char *buffer, int valread)
{
    char *command = strtok(buffer, unwanted_chars);
    char *arg = strtok(NULL, unwanted_chars);

    if (has_left(client, valread))
        return;
    fprintf(stderr, "\033[93mLOG: Request received from %s:%d\n\033[0m",
        client->address, client->port);
    if (!has_command(client, command))
        return;
    if (strtok(NULL, unwanted_chars) != NULL) {
        print_response(client->fd, 501, "");
        return;
    }
    for (int i = 0; i < NB_COMMANDS; i++)
        if (strcmp(command, commands[i].name) == 0) {
            chdir(client->path);
            commands[i].func(client, arg);
            return;
        }
    print_response(client->fd, 500, "");
}
