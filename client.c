#include <SDL.h>
#include "socket.h"
#include "client.h"
#include "client_actions.h"
#include "map.h"
#include "display.h"


static int handle_event(SDL_Event* event, socket_holder sh, t_player_info* infos)
{
  if (event->type == SDL_QUIT)
    return 0;
  else if (event->type == SDL_KEYDOWN)
    handle_action(&event->key, sh, infos);
  return 1;
}

static SDL_Window	*window(void)
{
  if (SDL_Init(SDL_INIT_VIDEO) != 0)
    ERR_MSG("SDL init error: %s", SDL_GetError());

  SDL_Window* pWindow = NULL;
  pWindow = SDL_CreateWindow("Bomberman", SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED,
      MAP_ROW * TILE_WIDTH,
      MAP_COL * TILE_HEIGHT,
      SDL_WINDOW_SHOWN);

  return pWindow;
}

int	game_is_finish(t_game *game, int userIndex)
{
  int totalAlive = 0;
  /* server will fake being userIndex=-1 as userIndex, when the host died, to keep the server running */
  if (userIndex != -1 && !game->players[userIndex].alive)
    return 1; /* we're dead, game is over for us */
  for (int i = 0; i < MAX_PLAYERS; i++)
    totalAlive += game->players[i].alive;
  return totalAlive < 2; /* if we have 0 or 1 player alive */
}

void	client(char* host, int port)
{
  t_game  *game;
  socket_holder sh = connect_to_server(host, port);
  SDL_Window* pWindow = window();
  if (!pWindow)
    return;

  int userIndex = 1, readSize;
  if ((readSize = read(sh, &userIndex, sizeof userIndex)) < (long)sizeof userIndex)
    ERR_MSG("Unable to read user index. errno=%d,size=%d\n", errno, readSize);
  printf("Logged in as player #%d\n", userIndex + 1);
  SDL_Event event;
  while (1) {
    int dc = 0; /* did disconnect? */
    game = (t_game*)read_from(sh, sizeof *game, &dc);
    if (!game && !dc) { /* no game fetched, but still connected? means EAGAIN, probably (since we're nonblocking) */
      usleep(SOCKET_TIME_BETWEEN);
      continue;
    }
    if (dc || game_is_finish(game, userIndex)) /* disconnected? lost? won? exit loop */
      break;
    while (SDL_PollEvent(&event))
      if (!handle_event(&event, sh, game->players + userIndex))
        return; /* user quit */
    display(SDL_GetWindowSurface(pWindow), game);
    free(game);
    if (SDL_UpdateWindowSurface(pWindow) < 0)
      ERR_MSG("Unable to update window surface\n");
  }
  if (!game)
    printf("Disconnected\n");
  else if (game->players[userIndex].alive)
    printf("You win\nGG WP\n");
  else
    printf("You are dead you lose\n");
  free(game);
}
