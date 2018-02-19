#ifndef GAME_H_
#define GAME_H_

#include "bomberman.h"
#include "server.h"

void  game_process(t_server*, t_client_request*, int userIndex);
void	game_tick(t_game*);
void	game_init_players(t_game*);

#endif
