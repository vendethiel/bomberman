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
  select(fds[numfds - 1] + 1, &s->readfs, NULL, NULL, &tv);
}

int  read_int(socket_holder sh, int* disconnected)
{
  if (*disconnected)
    return 0; /* are we already disconnected? give up... */
  int i;
  *disconnected = read_into(sh, (char*)&i, sizeof i);
  return i;
}

char  read_char(socket_holder sh, int* disconnected)
{
  if (*disconnected)
    return 0; /* are we already disconnected? give up... */
  char c;
  *disconnected = read_into(sh, &c, sizeof c);
  return c;
}

void send_int(socket_holder sh, int i)
{
  write(sh, (char*)&i, sizeof i);
}

void send_char(socket_holder sh, char c)
{
  write(sh, &c, sizeof c);
}

int  read_into(socket_holder sockfd, char* buffer, size_t left)
{
  char* buffLeft = buffer;
  while (left > 0) {
    int count = recv(sockfd, buffLeft, left, 0);
    if (count == -1 &&
#ifdef _WIN32
      WSAGetLastError() == WSAEWOULDBLOCK
#else
      errno == EAGAIN
#endif
      )
      continue; /* try again */
    if (count < 1)
      return 1;
    left -= count;
    buffLeft += count;
  }
  return 0;
}
