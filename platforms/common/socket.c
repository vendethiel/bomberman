#include "../../bomberman.h"
#include "../../socket.h"

void select_clients(socket_data* s, int numfds, socket_holder* fds)
{
  struct timeval tv;

  FD_ZERO(&s->readfs);

  for (int i = 0; i < numfds; ++i)
    if (-1 != fds[i])
      FD_SET(fds[i], &s->readfs);
  tv.tv_sec = tv.tv_usec = 0;
  select(fds[MAX_PLAYERS - 1] + 1, &s->readfs, NULL, NULL, &tv); /* TODO don't use MAX_PLAYERS here */
}

char*  read_from(socket_holder sockfd, size_t left, int* disconnected)
{
  char* buffer = malloc(left);
  if (!buffer)
    ERR_MSG("malloc failed for read_from");
  *disconnected = read_into(sockfd, buffer, left);
  return buffer;
}

int  read_into(socket_holder sockfd, char* buffer, size_t left)
{
  char* buffLeft = buffer;
  while (left > 0) {
    /* read should have be here by virtue of platforms/_/socket.h being included */
    int count = recv(sockfd, buffLeft, left, 0);
    if (count == -1 && errno == EAGAIN)
      continue; /* try again */
    if (count == 0)
      return 1;
    left -= count;
    buffLeft += count;
  }
  return 0;
}
