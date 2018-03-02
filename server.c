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
		/* TODO check whether a client disconnected */
    /* TODO make Ctrl-c interrupts work, someway, somehow */
		server->fds[i] = -1;
		while (-1 == server->fds[i])
			server->fds[i] = accept(server->sockfd, server->sock_ptr,
					&server->len);
		/* send user id */
		write(server->fds[i], &i, sizeof i);
		printf("Connected player #%d\n", i + 1);
	}
}

/* receives a command from the client
 * returns 0 on read length 0 (dc) */
static int	handle_client(t_server *server, fd_set *readfs, int userIndex)
{
	if (!server->game.players[userIndex].alive)
		return 1;
	int sockfd = server->fds[userIndex];
	char	buffer[sizeof(t_client_request)];

	if (FD_ISSET(sockfd, readfs))
	{
		size_t left = sizeof(t_client_request);
		char *buffLeft = buffer;
		while (left > 0)
		{
			int count = read(sockfd, buffer, left);
			if (count == 0)
			{
				FD_CLR(sockfd, readfs);
				return 0;
			}
			left -= count;
			buffLeft += count;
		}
		FD_CLR(sockfd, readfs);
		game_process(server, (t_client_request*)buffer, userIndex);
	}
	return 1;
}

static void*	game_start(void* _server)
{
	t_server *server = _server;
	struct timeval	tv;
	fd_set	readfs;

	bind_clients(server);
	map_init(server->game.map);
	game_init_players(&server->game);
	while (server->running) /* TODO mutex */
	{
		FD_ZERO(&readfs);
		for (int i = 0; i < MAX_PLAYERS; ++i)
			if (-1 == server->fds[i])
				return NULL;
			else
				FD_SET(server->fds[i], &readfs);
		tv.tv_sec = tv.tv_usec = 0;
		select(server->fds[MAX_PLAYERS - 1] + 1, &readfs, NULL, NULL, &tv);
		/* read actions for each player */
		for (int i = 0; i < MAX_PLAYERS; ++i)
			if (server->fds[i] > 0 && !handle_client(server, &readfs, i))
				return NULL;
		game_tick(&server->game);
		for (int i = 0; i < MAX_PLAYERS; ++i) {
      // TODO send less data, we don't need to send i.e. infos on the bombs
			if (server->fds[i] > 0) /* don't write to dc'd client, prevent SIGPIPE */
				write(server->fds[i], &server->game, sizeof server->game);
    }
		usleep(SOCKET_TIME_BETWEEN);
	}
	return NULL;
}

//Configure server socket
static int  prepare_server(t_server* server)
{
	int reuseopt = 1;
	server->len = sizeof(struct sockaddr);
	server->sock_ptr = (struct sockaddr*)&server->sock_serv;
	server->sockfd = socket(AF_INET, SOCK_STREAM, 0);
	setsockopt(server->sockfd, SOL_SOCKET, SO_REUSEADDR, &reuseopt, sizeof reuseopt);
	if (-1 == server->sockfd)
		ERR_MSG("server sockfd is -1\n");
	server->sock_serv.sin_family = AF_INET;
	server->sock_serv.sin_port = htons(server->port);
	server->sock_serv.sin_addr.s_addr = INADDR_ANY;
	if (-1 == bind(server->sockfd, server->sock_ptr, server->len))
		ERR_MSG("could not bind, errno=%d\n", errno);
	listen(server->sockfd, MAX_PLAYERS);
	return 1;
}

int	server(int port)
{
	t_server server;
	void* discard_return;

	signal(SIGPIPE, SIG_IGN); /* discard SIGPIPE signals */
	set_running(server, 1);
	server.port = port;

	if (!prepare_server(&server))
		return 1;
	pthread_create(&server.tid, NULL, game_start, &server);
	client("127.0.0.1", server.port);

	while (is_running(server) && !game_is_finish(&server.game, -1))
	{ /* wait for other players to end the game */ }
	set_running(server, 0);
	pthread_join(server.tid, &discard_return);
	return 0;
}
