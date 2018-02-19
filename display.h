#ifndef DISPLAY_H_
#define DISPLAY_H_

#include "SDL.h"
#include "bomberman.h"

void	display(SDL_Surface *screen, t_game *game/*, t_player_info *player*/);

typedef struct s_tile {
  int x;
  int y;
} t_tile;

#endif
