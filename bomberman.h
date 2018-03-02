#ifndef BOMBERMAN_H_
#define BOMBERMAN_H_

#include <sys/types.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAX_PLAYERS 2
#define MAP_COL 9 /* y | */
#define MAP_ROW 9 /* x --- */
#define MAP_SIZE (MAP_COL * MAP_ROW)
#define TILE_HEIGHT 16 /* y */
#define TILE_WIDTH 16 /* x */

/* to usleep() for server, to throttle for client. 100000 = 0.1s */
#define SOCKET_TIME_BETWEEN 100000

typedef struct  s_client_request
{
        unsigned int  magic;                  /* Un magic number commun entre le client et le serveur, ou l'identifiant d'un type de structure */
        int           x_pos;                  /* La position x souhait?e par le client */
        int           y_pos;                  /* La position y souhait?e par le client */
        int           dir;                    /* La direction souhait?e par le client */
        int           command;                /* Une commande du client (0 : Ne rien faire / 1 : Poser une bombe) */
        int           speed;                  /* La vitesse du joueur */
        int           ckecksum;               /* Un checksum simple */
}               t_client_request;

typedef struct s_player_info
{
        char  connected;
        char  alive;
        int   x_pos;
        int   y_pos;
        int   current_dir;
        int   current_speed;
        int   max_speed;
        int   bombs_left;
        int   bombs_capacity;
        int   frags;
}		t_player_info;

typedef char map_cell_t;
typedef map_cell_t t_map[MAP_SIZE];

#define BOMB_TICKS 40
typedef struct s_bomb
{
	int	ticks_left;
	int y;
	int x;
} t_bomb;

typedef struct          s_game
{
        t_player_info        players[MAX_PLAYERS];
        t_map                map;
				t_bomb* bomb;
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
