#ifndef MAP_H__
#define MAP_H__

#include "bomberman.h"

enum e_map_flag {
	map_flag_bonus = 0x04,
	map_flag_burning = 0x08,
	map_flag_bomb = 0x10,
	map_flag_breakable_wall = 0x20,
	map_flag_wall = 0x40,
};

void	map_init(map_cell_t*);
map_cell_t	map_get(map_cell_t*, int y, int x);
void	map_set(map_cell_t*, int y, int x, map_cell_t val);
int	map_cell_burning(map_cell_t cell);
int	map_is_wall(map_cell_t cell);
int map_is_breakable_wall(map_cell_t cell);
int map_has_bomb(map_cell_t cell);
int map_has_bonus(map_cell_t cell);
int	map_get_bonus(map_cell_t cell);

#endif
