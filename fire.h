/* This file is part of Alienwave, a game by Alessandro Pira */

#ifndef _FIRE_H
#define _FIRE_H

typedef struct
{
	int x;
	int y;
	void (*blit)(int,int);
	void (*clear)(int,int);
//	int state; // for future use
//	int type;  // for future use
} fire;

#define NUM_FIRES 25

void new_fire(int, int);
void init_fires();
void blit_fires();
void delete_fires();
void move_fires();

#endif //_FIRE_H
