#ifndef MAP_H__
#define MAP_H__

#include "bomberman.h"

enum e_map_flag {
	map_flag_bomb = 0x10,
	map_flag_breakable_wall = 0x20,
	map_flag_wall = 0x40,
	map_flag_burning = 0x80,
	map_flag_bonus = 0x08,
};

void	map_init(char*);
char	map_get(char*, int y, int x);
void	map_set(char*, int y, int x, char val);
int	map_cell_burning(char cell);
int	map_is_wall(char cell);
int map_is_breakable_wall(char cell);
int map_has_bomb(char cell);
int map_has_bonus(char cell);
int	map_get_bonus(char cell);

#endif
