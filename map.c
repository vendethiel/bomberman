#include <string.h>
#include "map.h"

void	map_init(map_cell_t* map)
{
	memset(map, 0, MAP_SIZE);
	for (int i = 0; i < MAP_ROW; ++i)
	{
		map[i] |= map_flag_wall; /* top wall */
		map[MAP_SIZE - 1 - i] |= map_flag_wall; /* bottom wall */
	}
	for (int i = 1; i < MAP_COL - 1;)
	{
		map[i * MAP_ROW] |= map_flag_wall; /* left wall */
		if (i % 2 == 0)
		{
			map[i * MAP_ROW + 2] = map[i * MAP_ROW + 6] = map_flag_wall + map_flag_breakable_wall;
			map[i * MAP_ROW + 6] = map_flag_wall;
		}
		map[++i * MAP_ROW - 1] |= map_flag_wall; /* right wall */
	}
}

char	map_get(map_cell_t* map, int y, int x)
{
	return map[x + y * MAP_ROW];
}

void	map_set(map_cell_t* map, int y, int x, map_cell_t val)
{
	map[x + y * MAP_ROW] = val;
}

int	map_cell_burning(map_cell_t cell)
{
	return cell & map_flag_burning;
}

int	map_is_wall(map_cell_t cell)
{
	return cell & map_flag_wall;
}

int map_is_breakable_wall(map_cell_t cell)
{
	return map_is_wall(cell) && (cell & map_flag_breakable_wall);
}

int map_has_bomb(map_cell_t cell)
{
	return cell & map_flag_bomb;
}

int map_has_bonus(map_cell_t cell)
{
	return cell & map_flag_bonus;
}

int	map_get_bonus(map_cell_t cell)
{
	/* return 3 LSBs */
	return cell & 0x07;
}
