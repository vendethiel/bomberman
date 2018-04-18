#ifndef PLATFORMS_WINDOWS_SOCKET_H_
#define PLATFORMS_WINDOWS_SOCKET_H_

#define PLATFORMS_SPECIFIC_SOCKET_H_

#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")


typedef SOCKET socket_holder;

typedef struct s_socket_data {
  SOCKADDR_IN sock_serv;
  SOCKET sockfd;
  struct sockaddr	*sock_ptr;
  int len;
  fd_set readfs;
} socket_data;

#endif
