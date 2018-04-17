#ifndef PLATFORMS_POSIX_SOCKET_H_
#define PLATFORMS_POSIX_SOCKET_H_

#define PLATFORMS_SPECIFIC_SOCKET_H_

#include <sys/types.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>

typedef int socket_holder;

typedef struct s_socket_data {
  struct sockaddr_in	sock_serv;
  struct sockaddr	*sock_ptr;
  socklen_t	len;
  int sockfd;
  fd_set readfs;
} socket_data;

#endif
