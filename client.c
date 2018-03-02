#include <SDL.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include "err.h"
#include "client.h"
#include "client_actions.h"
#include "map.h"
#include "display.h"

int connect_to_server(const char* addr, int port)
{
  int sockfd;
  struct sockaddr_in serv;

  printf("Connecting to %s:%i\n", addr, port);
  sockfd = socket(AF_INET, SOCK_STREAM, 0); 
  if (sockfd < 0)
    ERR_MSG("Could not open socket, sockfd=%d\n", sockfd);
  serv.sin_family = AF_INET;
  serv.sin_port = htons(port);
  serv.sin_addr.s_addr = inet_addr(addr);
  if (-1 == connect(sockfd, (struct sockaddr*)&serv, sizeof serv))
    ERR_MSG("Connect returned -1. errno=%d\n", errno);
  int flags = fcntl(sockfd, F_GETFL, 0);
  if (fcntl(sockfd, F_SETFL, flags | O_NONBLOCK))
    ERR_MSG("Unable to set client sockfd to nonblocking. errno=%d\n", errno);
  return sockfd;
}


static int handle_event(SDL_Event* event, int sockfd, t_player_info* infos)
{
  if (event->type == SDL_QUIT)
    return 0;
  else if (event->type == SDL_KEYDOWN)
    handle_action(&event->key, sockfd, infos);
  return 1;
}

static SDL_Window	*window(void)
{
  if (SDL_Init(SDL_INIT_VIDEO) != 0)
  {
    printf("SDL init error: %s", SDL_GetError());
    return NULL;
  }

  SDL_Window* pWindow = NULL;
  pWindow = SDL_CreateWindow("Bomberman", SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED,
      MAP_ROW * TILE_WIDTH,
      MAP_COL * TILE_HEIGHT,
      SDL_WINDOW_SHOWN);

  return pWindow;
}

static t_game*  read_game(int sockfd)
{
  char* buffer = malloc(sizeof(t_game));
  char* buffLeft = buffer;
  size_t left = sizeof(t_game);
  while (left > 0) {
    int count = read(sockfd, buffLeft, left);
    if (count == -1 && errno == EAGAIN)
      continue; /* try again */
    if (count == 0)
      return NULL; /* TODO signal disconnect */
    left -= count;
    buffLeft += count;
  }
  return (t_game*)buffer;
}


int	game_is_finish(t_game *game, int userIndex)
{
  int totalAlive = 0;
  /* server passes -1 as userIndex, so that when the first player dies(server),
   * the game continues */
  if (userIndex != -1 && !game->players[userIndex].alive) {
    return 1; /* we're dead, game is over for us */
  }
  for (int i = 0; i < MAX_PLAYERS; i++) {
    totalAlive += game->players[i].alive;
  }
  return totalAlive < 2; /* if we have 0 or 1 player alive */
}

void	client(char* host, int port)
{
  t_game  *game;
  int sockfd = connect_to_server(host, port);
  SDL_Window* pWindow = window();
  if (!pWindow)
    return;

  int userIndex = 0, readSize;
  if ((readSize = read(sockfd, &userIndex, sizeof userIndex)) < (long)sizeof userIndex)
    ERR_MSG("Unable to read user index. errno=%d,size=%d\n", errno, readSize);
  printf("Logged in as player #%d\n", userIndex);
  SDL_Event event;
  while (1) {
    game = read_game(sockfd);
    if (!game) {
      usleep(SOCKET_TIME_BETWEEN);
      continue;
    }
    if (game_is_finish(game, userIndex))
      break;
    while (SDL_PollEvent(&event))
      if (!handle_event(&event, sockfd, game->players + userIndex))
        return; /* user exited */
    display(SDL_GetWindowSurface(pWindow), game/*, game->players + userIndex*/);
    free(game);
    if (SDL_UpdateWindowSurface(pWindow) < 0)
      ERR_MSG("Unable to update window surface\n");
  }
  if (game->players[userIndex].alive)
    printf("You win\nGG WP\n");
  else
    printf("You are dead you lose\n");
}
