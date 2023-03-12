/*
** EPITECH PROJECT, 2023
** FTP [WSL: Ubuntu]
** File description:
** main
*/

#include "ftp.h"

int main(int argc, char **argv)
{
    server_t *server = NULL;

    handle_arguments(argc, argv);
    server = create_server(atoi(argv[1]), argv[2]);
    if (server == NULL)
        return EXIT_ERROR;
    if (setup_signal())
        return EXIT_ERROR;
    if (server_loop(server) != 0) {
        delete_server(server);
        return EXIT_ERROR;
    }
    delete_server(server);
    return EXIT_SUCCESS;
}
