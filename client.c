#include "bomberman.h"
#include "socket.h"
#include "thread.h"
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

SDL_Window	*window(void)
{
  static SDL_Window *w;
  if (!w)
    w = SDL_CreateWindow(
      "Bomberman",
      SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED,
      MAP_ROW * TILE_WIDTH,
      MAP_COL * TILE_HEIGHT,
      SDL_WINDOW_SHOWN);
  return w;
}

int	game_is_finish(t_game *game, int userIndex)
{
  int totalAlive = 0;
  /* server will fake being userIndex=-1 as userIndex, when the host died, to keep the server running */
  if (userIndex != -1 && !game->players[userIndex].alive)
    return 1; /* we're dead, game is over for us */
  for (int i = 0; i < game->num_players; i++)
    totalAlive += game->players[i].alive;
  return totalAlive < 2; /* if we have 0 or 1 player alive */
}

static void read_game(socket_holder sh, t_game* game, int* dc)
{
  *dc = 0;
  for (int i = 0; i < game->num_players; ++i) {
    game->players[i].alive = read_int(sh, dc);
    game->players[i].x_pos = read_int(sh, dc);
    game->players[i].y_pos = read_int(sh, dc);
  }
  for (int i = 0; i < MAP_SIZE; ++i) {
    game->map[i] = read_char(sh, dc);
  }
}

void	client(char* host, int port)
{
  t_game  game;
  int dc = 0, userIndex = 0; /* did disconnect?, user index, num players */
  socket_holder sh = connect_to_server(host, port);
  SDL_Window* pWindow = window();
  if (!pWindow)
    return;

  userIndex = read_int(sh, &dc);
  game.num_players = read_int(sh, &dc);
  if (dc)
    ERR_MSG("Unable to read user index/numPlayers. errno=%d\n", errno);
  game.players = malloc(game.num_players * sizeof(t_player_info));
  printf("Logged in as player #%d/%d\n", userIndex + 1, game.num_players);
  SDL_Event event;
  while (1) {
    read_game(sh, &game, &dc);
    if (dc || game_is_finish(&game, userIndex)) /* disconnected? lost? won? exit loop */
      break;
    while (SDL_PollEvent(&event))
      if (!handle_event(&event, sh, game.players + userIndex))
        return; /* user quit */
    display(SDL_GetWindowSurface(pWindow), &game);
    if (SDL_UpdateWindowSurface(pWindow) < 0)
      ERR_MSG("Unable to update window surface\n");
    sleep_ms(SOCKET_TIME_BETWEEN);
  }
  if (dc)
    printf("Disconnected\n");
  else if (game.players[userIndex].alive)
    printf("You win\nGG WP\n");
  else
    printf("You are dead you lose\n");
  free(game.players);
  SDL_DestroyWindow(pWindow);
}
