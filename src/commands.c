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

static bool check_status(client_t *client, char *buffer, int valread)
{
    if (valread == 0) {
        exec_quit(client, NULL);
        return false;
    }
    if (strlen(client->input_buffer) + strlen(buffer) > MAX_BUFFER_SIZE) {
        exec_quit(client, NULL);
        return false;
    }
    return true;
}

static bool has_command(client_t *client, char *command)
{
    if (command == NULL) {
        print_response(client->fd, 500, "");
        return false;
    }
    return true;
}

void on_command(client_t *client, char *buffer)
{
    char *command = strtok(buffer, unwanted_chars);
    char *arg = strtok(NULL, unwanted_chars);

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

void handle_commands(client_t *client, char *buffer, int valread)
{
    char *idx_ptr = NULL;
    char *line_break_ptr = NULL;
    char tmp_buffer[MAX_BUFFER_SIZE] = {0};

    if (!check_status(client, buffer, valread)) {
        return;
    }
    idx_ptr = strcat(client->input_buffer, buffer);
    line_break_ptr = strchr(idx_ptr, '\n');
    while (line_break_ptr) {
        memcpy(tmp_buffer, idx_ptr, line_break_ptr - idx_ptr + 1);
        on_command(client, tmp_buffer);
        memmove(client->input_buffer, line_break_ptr + 1,
            strlen(line_break_ptr + 1) + 1);
        memset(tmp_buffer, 0, MAX_BUFFER_SIZE);
        idx_ptr = line_break_ptr + 1;
        line_break_ptr = strchr(idx_ptr, '\n');
    }
}
