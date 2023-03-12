/*
** EPITECH PROJECT, 2023
** FTP [WSL : Ubuntu]
** File description:
** signal
*/

#include "ftp.h"

static void signal_handler(int sig)
{
    if (sig == SIGINT) {
        fprintf(stderr, "\033[41m\033[30mLOG: SERVER CLOSED\n\033[0m");
        exit(0);
    }
}

int setup_signal(void)
{
    struct sigaction sa;

    sa.sa_handler = signal_handler;
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        return ERROR;
    }
    return NO_ERROR;
}
