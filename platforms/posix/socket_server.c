#include "../../bomberman.h"
#include "socket.h"
#include "../common/socket.h"

void write_to(int fd, char* data, size_t size)
{
  if (fd != -1)
    write(fd, data, size);
}

void accept_client(socket_holder* fd, socket_data* s)
{
  /* TODO check whether a client disconnected */
  *fd = -1;
  while (-1 == *fd)
    *fd = accept(s->sockfd, s->sock_ptr, &s->len);
}

read_request read_client_request(socket_holder* fd, socket_data* s, char* buffer)
{
  (void)s;
  if (*fd == -1)
    return read_already_dc;

	if (FD_ISSET(*fd, &s->readfs))
	{
		size_t left = sizeof(t_client_request);
		char *buffLeft = buffer;
		while (left > 0)
		{
			int count = read(*fd, buffer, left);
			if (count < 0)
				continue;
			else if (count == 0)
			{
				*fd = 0;
				FD_CLR(*fd, &s->readfs);
				return read_disconnect;
			}
			left -= count;
			buffLeft += count;
		}
		FD_CLR(*fd, &s->readfs);
    return read_ok;
  }
  return read_none;
}

void select_clients(socket_data* s, int numfds, socket_holder* fds)
{
	struct timeval	tv;

  FD_ZERO(&s->readfs);

  for (int i = 0; i < numfds; ++i)
    if (-1 != fds[i])
      FD_SET(fds[i], &s->readfs);
  tv.tv_sec = tv.tv_usec = 0;
  select(fds[MAX_PLAYERS - 1] + 1, &s->readfs, NULL, NULL, &tv); /* TODO don't use MAX_PLAYERS here */
}

void socket_prepare_data(socket_data* s, int port)
{
	int reuseopt = 1;
	s->len = sizeof(struct sockaddr);
	s->sock_ptr = (struct sockaddr*)&s->sock_serv;
	s->sockfd = socket(AF_INET, SOCK_STREAM, 0);
	setsockopt(s->sockfd, SOL_SOCKET, SO_REUSEADDR, &reuseopt, sizeof reuseopt);
	if (-1 == s->sockfd)
		ERR_MSG("s sockfd is -1\n");
	s->sock_serv.sin_family = AF_INET;
	s->sock_serv.sin_port = htons(port);
	s->sock_serv.sin_addr.s_addr = INADDR_ANY;
	if (-1 == bind(s->sockfd, s->sock_ptr, s->len))
		ERR_MSG("could not bind, errno=%d\n", errno);
	listen(s->sockfd, MAX_PLAYERS);
}
