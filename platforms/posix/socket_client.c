#include <unistd.h>
#include "../../bomberman.h"
#include "../../socket.h"

socket_holder connect_to_server(const char* addr, int port)
{
  socket_holder sockfd;
  struct sockaddr_in serv;

  printf("Connecting to %s:%i\n", addr, port);
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0)
  ERR_MSG("Could not open socket, sockfd=%d\n", sockfd);
  serv.sin_family = AF_INET;
  serv.sin_port = htons(port);
  serv.sin_addr.s_addr = inet_addr(addr);
  if (-1 == connect(sockfd, (struct sockaddr*)&serv, sizeof serv))
  ERR_MSG("Connect returned while trying to connect to %s:%d -1. errno=%d\n", addr, port, errno);
  int flags = fcntl(sockfd, F_GETFL, 0);
  if (fcntl(sockfd, F_SETFL, flags | O_NONBLOCK))
    ERR_MSG("Unable to set client sockfd to nonblocking. errno=%d\n", errno);
  return sockfd;
}
