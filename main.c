#include <SDL.h>
#include "bomberman.h"
#include "main.h"
#include "client.h"
#include "server.h"

int	main(int argc, char** argv)
{
  if (argc == 4 && !strcmp(argv[1], "client"))
    client(argv[2], atoi(argv[3]));
  else if (argc == 3 && !strcmp(argv[1], "server"))
    return server(atoi(argv[2]));
  else
    printf("Usage:\n  %1$s server [port]\n  %1$s client [host] [port]\n", argv[0]);
}
