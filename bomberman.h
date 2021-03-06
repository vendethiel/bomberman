#ifndef BOMBERMAN_H_
#define BOMBERMAN_H_

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#ifdef _WIN32
#define SDL_MAIN_HANDLED
#include <SDL2\SDL.h>
#include <SDL2\SDL_image.h>
#else
#include <SDL.h>
#include <SDL_image.h>
#endif

#include "err.h"

#define MAP_COL 9 /* y | */
#define MAP_ROW 9 /* x --- */
#define MAP_SIZE (MAP_COL * MAP_ROW)
#define TILE_HEIGHT 16 /* y */
#define TILE_WIDTH 16 /* x */

/* to sleep_ms() for server, to throttle for client. 100ms = 0.1s */
#define SOCKET_TIME_BETWEEN 100

typedef struct  s_client_request
{
        int           x_pos;                  /* La position x souhait?e par le client */
        int           y_pos;                  /* La position y souhait?e par le client */
        int           command;                /* Une commande du client (0 : Ne rien faire / 1 : Poser une bombe) */
}               t_client_request;

typedef char map_cell_t;
typedef map_cell_t t_map[MAP_SIZE];

#define BOMB_TICKS 40
typedef struct s_bomb
{
	int	ticks_left;
	int y;
	int x;
} t_bomb;

typedef struct s_player_info
{
        char  alive;
        int   x_pos;
        int   y_pos;
}		t_player_info;


typedef struct          s_game
{
        t_player_info*        players;
        t_map                map;
				t_bomb* bomb;
        int num_players;
}                       t_game;


/*
** Bit 0 : Indique si la case est en flammes (1) ou non (0)
** Bits [1..2] : Indique le type de terrain ( 00 : Terrain vide, 10 : Brique indestructible, 11 : Brique destructible). Note : Combinaison 01 inutilis?e.
** Bit 3 : Pr?sence d'une bombe (0 : Pas de bombe, 1 : Bombe)
** Bit 4 : Pr?sence d'un bonus / malus (0 : Pas de bonus / malus, 1 : Bonus / malus pr?sent)
** Bits [5..7] : Type de bonus / malus.
**
** Pour l'exemple, liste des bonus / malus
** 000 : Bonus port?e bombes
** 001 : Malus port?s bombes
** 010 : Bonus nombre bombes
** 011 : Malus nombre bombes
** 100 : Bonus vitesse
** 101 : Malus vitesse
** 110 : Rien
** 111 : Rien
*/

#endif
