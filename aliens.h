/* This file is part of Alienwave, a game by Alessandro Pira */

#ifndef _ALIENS_H
#define _ALEINS_H

#define AT_NONE    -1
#define AT_LAST    -2
#define AT_BIG_EXP  8
#define AT_LIT_EXP  7
#define AT_XSARNA_1 6
#define AT_XSARNA_2 5
#define AT_TINY     4
#define AT_SLIME    3
#define AT_BALL     2
#define AT_BIG      1
#define AT_LITTLE   0

#define MAX_HEIGHT 5

typedef char bitmask[MAX_HEIGHT];

typedef struct
{
	int x;
	int y;
	int type; // See #defines up there
	void (*blit)(int,int);
	void (*clear)(int,int);
	void (*move)(void *);
	short int state;
	bitmask collide;
} alien;

#define NUM_ALIENS 10

/* Alien movement */
void move_alien_straight(void *);
void move_alien_oscillate(void *);
void move_alien_serpent(void *);
void move_alien_diagonal(void *);

void init_aliens();

/* Draws all aliens */
void blit_aliens();

/* Deletes all aliens */
void delete_aliens();

/* Makes all aliens move */
void move_aliens();

/* Blows alien num and update score */
void blow_alien(int);

/* Check collisions for all aliens */
int collide_aliens(int, int);

#endif //_ALIENS_H
