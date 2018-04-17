#include <stdio.h>
#include "err.h"
#include "../../socket.h"

void socket_prepare(void)
{
  static WSADATA data;
  WSAStartup(MAKEWORD(2, 0), &data);
}

void socket_cleanup(void)
{
  WSACleanup();
}

void write_to(int fd, char* data, size_t size)
{
  /*
  if (fd != -1)
    write(fd, data, size);
   */
}

read_request read_client_request(socket_holder* fd, socket_data* s, char* buffer)
{
  return read_ok; /* TODO */
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
  s->len = sizeof(SOCKADDR);
  if (s->sockfd == INVALID_SOCKET)
    ERR_MSG("sockfd is INVALID_SOCKET\n");
  bind(s->sockfd, (SOCKADDR*)&s->sock_serv, s->len);
  /* TODO use the equiv to fcntl to set nonblocking */
}
