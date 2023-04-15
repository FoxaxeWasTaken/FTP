/*
** EPITECH PROJECT, 2023
** FTP [WSL : Ubuntu]
** File description:
** help
*/

#include "ftp.h"

static const help_t help[NB_HELP] = {
    {NULL, "Commands supported: USER PASS CWD CDUP QUIT DELE PWD NOOP,"
    " Type HELP <command> for more information."},
    {"HELP", "HELP [<SP> <string>] <CRLF> : List available commands"},
    {"USER", "USER <SP> <username> <CRLF> : Specify user for authentication"},
    {"PASS", "PASS <SP> <password> <CRLF> : Specify password for "
    "authentication"},
    {"CWD", "CWD  <SP> <pathname> <CRLF> : Change working directory"},
    {"CDUP", "CDUP <CRLF> : Change working directory to parent directory"},
    {"QUIT", "QUIT <CRLF> : Disconect from server"},
    {"DELE", "DELE <SP> <pathname> <CRLF> : Delete file on the server"},
    {"PWD", "PWD  <CRLF> : Print working directory"},
    {"NOOP", "NOOP <CRLF> : Do nothing"},
    {"PASV", "PASV <CRLF> : Enable \"passive\" mode for data transfer"},
    {"PORT", "PORT <SP> <host-port> <CRLF> : Enable \"active\" mode for data "
    "transfer"},
    {"RETR", "RETR <SP> <pathname> <CRLF> : Download file from server to "
    "client"},
    {"STOR", "STOR <SP> <pathname> <CRLF> : Upload file from client to server"},
    {"LIST", "LIST <CRLF> : List files in current directory"}
};

void exec_help(client_t *client, char *args)
{
    if (args == NULL) {
        print_response(client->fd, 214, help[0].message);
        return;
    }
    for (int i = 1; i < NB_HELP; i++)
        if (strcmp(args, help[i].name) == 0) {
            print_response(client->fd, 214, help[i].message);
            return;
        }
    print_response(client->fd, 500, "");
}
