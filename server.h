#ifndef SERVER_H_
#define SERVER_H_

#include <pthread.h>
#include <SDL.h>
#include "main.h"
#include "bomberman.h"
#include "server_state.h"
#include "socket.h"

int	server(int host);

typedef struct s_server {
        pthread_t tid;
        t_game	game;
        socket_holder socks[MAX_PLAYERS];
        socket_data sock;
        int port;
        int running;
        pthread_mutex_t mutex;
} t_server;


int is_running(t_server* server);
void set_running(t_server* server, int value);


#endif

