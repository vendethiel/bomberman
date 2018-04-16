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
