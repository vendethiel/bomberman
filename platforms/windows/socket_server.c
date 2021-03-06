#include <stdio.h>
#ifndef __MINGW32__
#include <WS2tcpip.h>
#endif
#include "../../bomberman.h"
#include "../../err.h"
#include "../../socket.h"

void socket_prepare(void)
{
  static WSADATA data;
  if (0 != WSAStartup(MAKEWORD(2, 2), &data))
    ERR_MSG("WSAStartup failed!\n");
}

void socket_cleanup(void)
{
  WSACleanup();
}

void write_to(socket_holder fd, char* data, size_t size)
{
  if (fd != INVALID_SOCKET)
    send(fd, data, size, 0);
}

void accept_client(socket_holder* fd, socket_data* s)
{
  do {
    *fd = accept(s->sockfd, s->sock_ptr, &s->len);
  } while (*fd == INVALID_SOCKET);
}

void socket_prepare_data(socket_data* s, int port)
{
  s->sock_serv.sin_family = AF_INET;
  s->sock_serv.sin_port = htons((u_short) port);
  s->sock_serv.sin_addr.s_addr = INADDR_ANY;
  s->sockfd = socket(AF_INET, SOCK_STREAM, 0);
  s->len = sizeof(s->sock_serv);
  if (s->sockfd == INVALID_SOCKET)
    ERR_MSG("sockfd is INVALID_SOCKET: %d\n", WSAGetLastError());
  s->sock_ptr = (SOCKADDR*)&s->sock_serv;
  if (SOCKET_ERROR == bind(s->sockfd, s->sock_ptr, s->len))
    ERR_MSG("Unable to bind port %d: err=%d\n", port, WSAGetLastError());
  listen(s->sockfd, MAX_PLAYERS);
  u_long mode = 1; /* nonblocking mode */
  ioctlsocket(s->sockfd, FIONBIO, &mode);
  printf("Server ready\n");
  /* TODO use the equiv to fcntl to set nonblocking */
}
