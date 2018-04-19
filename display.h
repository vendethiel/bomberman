#ifndef DISPLAY_H_
#define DISPLAY_H_

#include "bomberman.h"

void	display(SDL_Surface *screen, t_game *game);

typedef struct s_tile {
  int x;
  int y;
} t_tile;

#endif
