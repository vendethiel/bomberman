#include <SDL.h>
#include "bomberman.h"
#include "main.h"
#include "client.h"
#include "server.h"
#include <stdint.h>
#include <string.h>

#if CHAR_BIT != 8
# error Unsupported char size
#endif

#define IS_BIG_ENDIAN (!*(unsigned char *)&(uint16_t){1})

int	main(int argc, char** argv)
{
  if (sizeof(int) != 4 || IS_BIG_ENDIAN) {
    puts("Cannot run with such an environment.");
    return 1;
  }

  if (argc == 4 && !strcmp(argv[1], "client"))
    client(argv[2], atoi(argv[3]));
  else if (argc == 3 && !strcmp(argv[1], "server"))
    return server(atoi(argv[2]));
  else
    printf("Usage:\n  %1$s server [port]\n  %1$s client [host] [port]\n", argv[0]);
}
