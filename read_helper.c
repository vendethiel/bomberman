#include "bomberman.h"
#include "read_helper.h"

#define DEFINE_ENCODER(T) void encode_##T(T a, char* b) { \
  for (size_t i = 0; i < sizeof a; ++i) { \
    b[i] = a >> CHAR_BIT * i; \
  } \
}

#define DEFINE_DECODER(T) T decode_##T(char* b) { \
  T a = 0; \
  for (size_t i = 0; i < sizeof a; ++i) { \
    a |= b[i] << CHAR_BIT * i; \
  } \
  return a; \
}

#define DEFINE_WRITER(T) void write_##T(t_server *server, T a, int fd, fd_set *readfs, int userIndex, int* disconnected) { \
  char b[sizeof a]; \
  encode_##T(a, b); \
  write_of(t_server *server, fd, b, sizeof a, readfs, userIndex, disconnected); \
}

#define DEFINE_READER(T) T read_##T(int fd, int* disconnected) { \
  char* b = read_of(fd, sizeof(T), disconnected); \
  return decode_##T(b); \
}

int write_of(t_server *server, int sockfd, char* buffer, size_t size, fd_set *readfs, int userIndex, int* disconnected) {
	size_t left = size;
	char *buffLeft = buffer;
	while (left > 0)
	{
		int count = (int) read_of(sockfd, size, disconnected);
		if (count < 0)
			continue;
		else if (count == 0)
		{
			server->game.players[userIndex].alive = 0;
			server->fds[userIndex] = 0;
			FD_CLR(sockfd, readfs);
			return count;
		}
		left -= count;
		buffLeft += count;
	}
	return 0;
}


static t_game*  read_of(int sockfd, size_t size, int* disconnected)
{
  char* buffer = malloc(size);
  char* buffLeft = buffer;
  size_t left = size;
  while (left > 0) {
    int count = read(sockfd, buffLeft, left);
    if (count == -1 && errno == EAGAIN)
      continue; /* try again */
    if (count == 0)
      return (*disconnected = 1, NULL);
    left -= count;
    buffLeft += count;
  }
  return (t_game*)buffer;
}
