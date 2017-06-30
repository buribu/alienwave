/* This file is part of Alienwave, a game by Alessandro Pira */

#ifndef _XZARNA_H
#define _XZARNA_H

#define MAX_DAMAGE 100

#define QUEEN_HEIGHT 5

typedef unsigned short s_bitmask[QUEEN_HEIGHT];

typedef struct
{
	int enabled;
	int x;
	int y;
	void (*blit)(int,int,int);
	void (*clear)(int,int);
	short int damage;
	unsigned char eggs;
	s_bitmask collide;
} alien_queen;

void init_queen();
void start_xzarna();

/* Return 1 if Xzarna is dying */
int xzarna_exploding();

#define COL_SHIP   0
#define COL_FIRE   1
#define COL_SHIELD 2
int collide_queen(int,int,int);

void move_queen();

void blit_queen();

void delete_queen();

#endif //_XZARNA_H

