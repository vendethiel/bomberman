#include <errno.h>
#include "err.h"
#include "server.h"
#include "client.h"
#include "map.h"
#include "game.h"
#include "socket.h"
#include "thread.h"
#include "client.h"

static void bind_clients(t_server *server)
{
  printf("Binding clients (total %d)\n", server->game.num_players);
  server->socks = malloc(sizeof(socket_holder) * server->game.num_players);
  if (!server->socks)
    ERR_MSG("Unable to alloc sockets\n");
  for (int i = 0; i < server->game.num_players; ++i) {
    /* TODO make Ctrl-c interrupts work, someway, somehow */
    accept_client(&server->socks[i], &server->sock);
    /* send user id */
    send_int(server->socks[i], i);
    send_int(server->socks[i], server->game.num_players);
    printf("Connected player #%d\n", i + 1);
  }
}

/* receives a command from the client
 * returns 0 on read length 0 (dc) */
static int handle_client(t_server *server, int userIndex)
{
  if (!server->game.players[userIndex].alive)
    return 1;
  char buffer[sizeof(t_client_request)];

  switch (read_client_request(&server->socks[userIndex], &server->sock, buffer)) {
    case read_ok:
      game_process(server, (t_client_request *) buffer, userIndex);
      return 1;

    case read_already_dc:
    case read_none:
      return 1; /* say everything was alright */

    case read_disconnect:
    default: /* should not be necessary, but since you can cast anything to an enum... */
      server->game.players[userIndex].alive = 0;
      return 0;
  }
}

static void send_game(socket_holder sh, t_game* game)
{
  for (int i = 0; i < game->num_players; ++i) {
    send_int(sh, game->players[i].alive);
    send_int(sh, game->players[i].x_pos);
    send_int(sh, game->players[i].y_pos);
  }
  for (int i = 0; i < MAP_SIZE; ++i) {
    send_char(sh, game->map[i]);
  }
}

static void game_start(void *_server)
{
  t_server *server = _server;

  bind_clients(server);
  map_init(server->game.map);
  game_init_players(&server->game);
  while (is_running(server)) {
    select_clients(&server->sock, server->game.num_players, server->socks);
    /* read actions for each player */
    for (int i = 0; i < server->game.num_players; ++i)
      handle_client(server, i);
    game_tick(&server->game);
    for (int i = 0; i < server->game.num_players; ++i)
      send_game(server->socks[i], &server->game);
    sleep_ms(SOCKET_TIME_BETWEEN);
  }
}

SDL_Window	*window(void);
int server(int port, int numPlayers)
{
  t_server server;

  setup_signal_handlers();
  server.port = port;

  if (numPlayers < 2 || numPlayers > 4)
    ERR_MSG("Invalid number of players: 2 to 4 allowed.");
  window(); /* init window in main thread */
  socket_prepare_data(&server.sock, port, numPlayers);
  server.running = 1;
  server.game.num_players = numPlayers;
  server.game.players = malloc(numPlayers * sizeof(t_player_info));
  if (!server.game.players)
    ERR_MSG("could not alloc players\n");
  if (!mutex_init(&server.mutex))
    ERR_MSG("could not init mutex, errno=%d\n", errno);
  thread_create(&server.tid, game_start, &server);
  client("127.0.0.1", server.port);

  while (is_running(&server)) {
    /* wait for other players to end the game */
    sleep_ms(SOCKET_TIME_BETWEEN);
  }

  set_running(&server, 0);
  thread_join(server.tid);
  mutex_cleanup(&server.mutex);
  return 0;
}
