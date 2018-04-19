#include <stdint.h>
#include <string.h>
#include <limits.h>
#include "bomberman.h"
#include "main.h"
#include "client.h"
#include "server.h"

#if CHAR_BIT != 8
# error Unsupported char size CHAR_BIT
#endif

#define IS_BIG_ENDIAN (!*(unsigned char *)&(uint16_t){1})

static char* dumbread(void)
{
  char* line = malloc(100), *b = line;
  if (!line)
    ERR_MSG("Unable to read terminal");

  int i, c;
  for (i = 0; i < 99 && (c = fgetc(stdin)); ++i) {
    if (c == EOF || c == '\n')
      break;
    line[i] = c;
  }
  line[i] = 0;
  return b;
}

int	main(int argc, char** argv)
{
  SDL_SetMainReady();
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    ERR_MSG("SDL init error: %s", SDL_GetError());

  int ret = EXIT_SUCCESS;
  if (sizeof(int) != 4 || IS_BIG_ENDIAN)
    ERR_MSG("Cannot run on this platform.");

  socket_prepare();
  printf("Select mode: client, server: "); fflush(stdin);
  char* mode = dumbread();
  if (!strcmp(mode, "client")) {
    printf("IP to connect to: "); fflush(stdin);
    char* ip = dumbread();
    printf("Port to connect to: "); fflush(stdin);
    int port = atoi(dumbread());
    client(ip, port);
  } else if (!strcmp(mode, "server")) {
    printf("Port to connect to: "); fflush(stdin);
    int port = atoi(dumbread());
    printf("Number of players (2 to 4): "); fflush(stdin);
    int nump = atoi(dumbread());
    ret = server(port, nump);
  } else {
    puts("Invalid mode entered. Modes: server, client\n");
    ret = 1;
  }
  socket_cleanup();
  return ret;
}
