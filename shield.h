/* This file is part of Alienwave, a game by Alessandro Pira */

#ifndef _SHIELD_H
#define _SHIELD_H

typedef struct
{
	int x;
	int y;
	void (*blit)(int,int,int);
	void (*clear)(int,int);
	int state;
} shield;

#define SHIELD_MAX 100  // Duration time
#define SHIELD_MIN -100 // Recharge time
#define SHIELD_STEP 40  // Should be more than SHIELD_MAX/3

void init_shields();
void open_shields(int, int);
void blit_shields();
void clear_shields();
/* Actually it doesn't move, but I've called this function "move"
   for coherency whith other move functions. It only checks for
   collisions and shield charge */
void move_shields();

#endif //_SHIELD_H
