#include "../../bomberman.h"
#include "socket.h"
#include "../common/socket.h"

int connect_to_server(const char* addr, int port)
{
  int sockfd;
  struct sockaddr_in serv;

  printf("Connecting to %s:%i\n", addr, port);
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0)
    ERR_MSG("Could not open socket, sockfd=%d\n", sockfd);
  serv.sin_family = AF_INET;
  serv.sin_port = htons(port);
  serv.sin_addr.s_addr = inet_addr(addr);
  if (-1 == connect(sockfd, (struct sockaddr*)&serv, sizeof serv))
    ERR_MSG("Connect returned -1. errno=%d\n", errno);
  int flags = fcntl(sockfd, F_GETFL, 0);
  if (fcntl(sockfd, F_SETFL, flags | O_NONBLOCK))
    ERR_MSG("Unable to set client sockfd to nonblocking. errno=%d\n", errno);
  return sockfd;
}

char*  read_from(int sockfd, size_t left, int* disconnected)
{
  char* buffer = malloc(left);
  if (!buffer)
    ERR_MSG("malloc failed for read_from");
  char* buffLeft = buffer;
  while (left > 0) {
    int count = read(sockfd, buffLeft, left);
    if (count == -1 && errno == EAGAIN)
      continue; /* try again */
    if (count == 0)
      return (*disconnected = 1, NULL);
    left -= count;
    buffLeft += count;
  }
  return buffer;
}
