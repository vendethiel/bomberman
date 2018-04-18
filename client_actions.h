#ifndef HANDLE_ACTIONS_H_
#define HANDLE_ACTIONS_H_

#include "bomberman.h"
#include "socket.h"

void handle_action(SDL_KeyboardEvent* key, socket_holder sockfd, t_player_info* infos);

#endif
