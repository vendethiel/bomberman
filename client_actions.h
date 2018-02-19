#ifndef HANDLE_ACTIONS_H_
#define HANDLE_ACTIONS_H_

#include "bomberman.h"
#include <SDL.h>

void handle_action(SDL_KeyboardEvent* key, int sockfd, t_player_info* infos);

#endif
