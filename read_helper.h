#ifndef READ_HELPER_H_
#define READ_HELPER_H_

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "server.h"

int write_of(t_server *server, int sockfd, char* buffer, size_t size, fd_set *readfs, int userIndex, int* disconnected);
static t_game* read_of(int sockfd, size_t size, int* disconnected);

#endif
