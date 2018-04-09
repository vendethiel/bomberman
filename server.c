#include <errno.h>
#include <unistd.h>
#include "err.h"
#include "server.h"
#include "client.h"
#include "map.h"
#include "game.h"

static void	bind_clients(t_server *server)
{
	printf("Binding clients (total %d)\n", MAX_PLAYERS);
	for (int i = 0; i < MAX_PLAYERS; ++i)
	{
    /* TODO make Ctrl-c interrupts work, someway, somehow */
    accept_client(&server->socks[i], &server->sock);
		/* send user id */
		write_to(server->socks[i], (char*)&i, sizeof i);
		printf("Connected player #%d\n", i + 1);
	}
}

/* receives a command from the client
 * returns 0 on read length 0 (dc) */
static int	handle_client(t_server *server, int userIndex)
{
	if (!server->game.players[userIndex].alive)
		return 1;
	char	buffer[sizeof(t_client_request)];

  switch (read_client_request(&server->socks[userIndex], &server->sock, buffer)) {
    case read_ok:
      game_process(server, (t_client_request*)buffer, userIndex);
      return 1;

    case read_already_dc:
      return 1; /* say everything was alright */

    case read_disconnect:
      server->game.players[userIndex].alive = 0;
      return 0;
  }
}

static void*	game_start(void* _server)
{
	t_server *server = _server;

	bind_clients(server);
	map_init(server->game.map);
	game_init_players(&server->game);
	while (is_running(server)) {
    select_clients(&server->sock, MAX_PLAYERS, server->socks);
		/* read actions for each player */
		for (int i = 0; i < MAX_PLAYERS; ++i)
			handle_client(server, i); /* note: DCs don't stop the server anymore. Let's see if everything still works... */
		game_tick(&server->game);
		for (int i = 0; i < MAX_PLAYERS; ++i)
      write_to(server->socks[i], (char*)&server->game, sizeof server->game); /* TODO send less data */
		usleep(SOCKET_TIME_BETWEEN);
	}
	return NULL; /* for the thread... */
}

int	server(int port)
{
	t_server server;
	void* discard_return;

	signal(SIGPIPE, SIG_IGN); /* discard SIGPIPE signals */
	server.port = port;

  socket_prepare_data(&server.sock, port);
  server.running = 1;
	if (pthread_mutex_init(&server.mutex, NULL) != 0)
		ERR_MSG("could not init mutex, errno=%d\n", errno);
	pthread_create(&server.tid, NULL, game_start, &server);
	client("127.0.0.1", server.port);

	while (is_running(&server)) {
    /* TODO sleep-wait... cvar? */
    /* wait for other players to end the game */
  }

	set_running(&server, 0);
	pthread_join(server.tid, &discard_return);
  pthread_mutex_destroy(&server.mutex);
	return 0;
}
