/*
** EPITECH PROJECT, 2023
** FTP [WSL : Ubuntu]
** File description:
** binary_arguments
*/

#include "ftp.h"

static const char *binary_help = "USAGE: ./myftp port path\n\tport is the port "
    "number on which the server socket listens\n\tpath is the path to the home "
    "directory for the users\n";

static bool is_number(char *str)
{
    for (size_t i = 0; str[i]; i++) {
        if (!isdigit(str[i]))
            return false;
    }
    return true;
}

void handle_arguments(int argc, char **argv)
{
    if (argc != 3) {
        if (argc == 2 &&
            (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0)) {
            printf(binary_help);
            exit(EXIT_SUCCESS);
        }
        exit(EXIT_ERROR);
    }
    if (!is_number(argv[1]) || (atoi(argv[1]) < 1024 || atoi(argv[1]) > 65535))
        exit(EXIT_ERROR);
}
