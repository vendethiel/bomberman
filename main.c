#include <stdint.h>
#include <string.h>
#include <limits.h>
#include <SDL.h>
#include "bomberman.h"
#include "main.h"
#include "client.h"
#include "server.h"

#if CHAR_BIT != 8
# error Unsupported char size CHAR_BIT
#endif

#define IS_BIG_ENDIAN (!*(unsigned char *)&(uint16_t){1})

int	main(int argc, char** argv)
{
  int ret = EXIT_SUCCESS;
  if (sizeof(int) != 4 || IS_BIG_ENDIAN) {
    puts("Cannot run with such an environment.");
    return 1;
  }

  socket_prepare();
  if (argc == 4 && !strcmp(argv[1], "client"))
    client(argv[2], atoi(argv[3]));
  else if (argc == 3 && !strcmp(argv[1], "server"))
    ret = server(atoi(argv[2]));
  else
    printf("Usage:\n  %1$s server [port]\n  %1$s client [host] [port]\n", argv[0]);
  socket_cleanup();
  return ret;
}
