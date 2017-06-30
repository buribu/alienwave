/* This file is part of Alienwave, a game by Alessandro Pira */

#include "aliens.h"
#include "blit.h"
#include "levels.h"
#include "util.h"

extern int x_ofs;
extern int y_ofs;
extern int score;
extern int game_ended;

const bitmask bitmask_big_alien   = {0xF8,0xF8,0x70,0x00,0x00};
const bitmask bitmask_lit_alien   = {0xE0,0x40,0x00,0x00,0x00};
const bitmask bitmask_ball_alien  = {0xE0,0xE0,0x00,0x00,0x00};
const bitmask bitmask_slime_alien = {0xF8,0xF8,0x00,0x00,0x00};
const bitmask bitmask_tiny_alien  = {0x80,0x00,0x00,0x00,0x00};

alien all_aliens[NUM_ALIENS];

/* Straight down, half speed if state is initialized at 0, top speed if -1 */
void move_alien_straight(void *al_ptr)
{
	alien *al;
	al = (alien*)al_ptr;

	switch (al->state)
	{
	case 0:
		al->state=1;
		break;
	case 1:
		al->y++;
		al->state=0;
		break;
	case -1:
		al->y++;
		break;
	}
	if ((al->y)>23) al->type=AT_NONE;
}

/* Move down diagonally (left if state<0, right if >0) until half screen,
   then goes down and right on the half of the screen.
   Finally, when state reaches 0, moves down vertically. */
void move_alien_oscillate(void *al_ptr)
{
	alien *al;
	al = (alien*)al_ptr;

	if (al->state>0)
	{
		if ((al->y)<10) al->y++;
		al->x++;
		al->state--;
		if ((al->x)>73) al->state = -(al->state);
	}
	else if (al->state<0)
	{
		if ((al->y)<10) al->y++;
		al->x--;
		al->state++;
		if ((al->x)<1) al->state = -(al->state);
	}
	else
	{
		al->y++;
		if ((al->y)>24) al->type=AT_NONE;
	}
}

/* Moves down like a serpent, with x oscillating between +3 and -3,
   at half speed; state must be initialized at 0 */
void move_alien_serpent(void *al_ptr)
{
	int xs=0;
	alien *al;
	al = (alien*)al_ptr;

	if (al->state<0)
	{
		al->state = -al->state;
	}
	else
	{
		if (al->state>10) xs = -1;
		else if (al->state<8) xs = 1;
		if (al->state == 0)
		{
			al->state = 13;
			xs = -1;
		}

		al->x+=xs;
		al->y++;

		if (al->state == 10) al->state=1;
		if (al->state == 8) al->state=17;

		if (al->state>9) al->state--;
		else al->state++;

		al->state = -al->state;

		if ((al->y)>24) al->type=AT_NONE;
	}
}

/* Moves diagonally (to left if state<0, to right if state>0),
   at half speed if abs(state)=1, top speed if 2.
   There are 2 kind of good initialization:
   x<=39, state>0
   x>=39, state<0 */
void move_alien_diagonal(void *al_ptr)
{
	alien *al;
	al = (alien*)al_ptr;

	if (al->state>0)
	{
		al->x++;
		switch (al->state)
		{
		case 1:
			al->state=3;
			break;
		case 3:
			al->state=1;
		case 2:
			al->y++;
		}
	}
	else
	{
		al->x--;
		switch (al->state)
		{
		case -1:
			al->state = -3;
			break;
		case -3:
			al->state = -1;
		case -2:
			al->y++;
		}
	}
	if ((al->y)>24) al->type=AT_NONE;
}

void init_aliens()
{
	int i;
	for (i=0;i<NUM_ALIENS;i++)
		all_aliens[i].type=AT_NONE;
}

/* Draws all aliens */
void blit_aliens()
{
	int i;
	for (i=0;i<NUM_ALIENS;i++)
	{
		if (all_aliens[i].type != AT_NONE)
		{
			all_aliens[i].blit(all_aliens[i].x+x_ofs,all_aliens[i].y+y_ofs);
		}
	}
}

/* Deletes all aliens */
void delete_aliens()
{
	int i;
	for (i=0;i<NUM_ALIENS;i++)
	{
		if (all_aliens[i].type != AT_NONE)
		{
			all_aliens[i].clear(all_aliens[i].x+x_ofs,all_aliens[i].y+y_ofs);
		}
	}
}

/* Makes all aliens move */
void move_aliens()
{
	int i;
	if (!create_aliens())
	{
		game_ended = 1;
	}
	for (i=0;i<NUM_ALIENS;i++)
	{
		switch (all_aliens[i].type)
		{
		case AT_BIG:
		case AT_TINY:
		case AT_BALL:
		case AT_SLIME:
		case AT_LITTLE:
			all_aliens[i].move((void*)&all_aliens[i]);
			break;
		case AT_BIG_EXP:
			switch (all_aliens[i].state++)
			{
			case 0:
				all_aliens[i].blit = blit_explosion_3;
				all_aliens[i].clear = clear_explosion_3;
				break;
			case 2:
				all_aliens[i].blit = blit_explosion_4;
				all_aliens[i].clear = clear_explosion_4;
				break;
			case 4:
				all_aliens[i].blit = blit_explosion_3;
				all_aliens[i].clear = clear_explosion_3;
				break;
			case 6:
				all_aliens[i].blit = blit_explosion_2;
				all_aliens[i].clear = clear_explosion_2;
				break;
			case 8:
				all_aliens[i].blit = blit_explosion_1;
				all_aliens[i].clear = clear_explosion_1;
				all_aliens[i].type = AT_LAST;
				break;
			}
			break;
		case AT_LIT_EXP:
			switch (all_aliens[i].state++)
			{
			case 0:
				all_aliens[i].blit = blit_explosion_2;
				all_aliens[i].clear = clear_explosion_2;
				break;
			case 2:
				all_aliens[i].blit = blit_explosion_3;
				all_aliens[i].clear = clear_explosion_3;
				break;
			case 4:
				all_aliens[i].blit = blit_explosion_2;
				all_aliens[i].clear = clear_explosion_2;
				break;
			case 6:
				all_aliens[i].blit = blit_explosion_1;
				all_aliens[i].clear = clear_explosion_1;
				all_aliens[i].type = AT_LAST;
				break;
			}
			break;
		case AT_LAST:
			all_aliens[i].type = AT_NONE;
			break;
		}
	}
}

/* Blows alien num and update score */
void blow_alien(int num)
{
	int i;
	for (i=0;i<MAX_HEIGHT;i++)
		all_aliens[num].collide[i]=0x00;

	switch (all_aliens[num].type)
	{
	case AT_BIG:
		score+=50;
		all_aliens[num].type=AT_BIG_EXP;
		all_aliens[num].blit=blit_explosion_3;
		all_aliens[num].clear=clear_explosion_3;
		all_aliens[num].state=0;
		all_aliens[num].x+=2;
		all_aliens[num].y++;
		break;
	case AT_LITTLE:
		score+=50;
		all_aliens[num].type=AT_LIT_EXP;
		all_aliens[num].blit=blit_explosion_2;
		all_aliens[num].clear=clear_explosion_2;
		all_aliens[num].state=0;
		all_aliens[num].x++;
		break;
	case AT_SLIME:
		score+=100;
		all_aliens[num].type=AT_BIG_EXP;
		all_aliens[num].blit=blit_explosion_3;
		all_aliens[num].clear=clear_explosion_3;
		all_aliens[num].state=0;
		all_aliens[num].x+=3;
		all_aliens[num].y++;
		break;
	case AT_TINY:
		score+=300;
		all_aliens[num].type=AT_LIT_EXP;
		all_aliens[num].blit=blit_explosion_2;
		all_aliens[num].clear=clear_explosion_2;
		all_aliens[num].state=0;
		break;
	case AT_BALL:
		score+=200;
		all_aliens[num].type=AT_LIT_EXP;
		all_aliens[num].blit=blit_explosion_2;
		all_aliens[num].clear=clear_explosion_2;
		all_aliens[num].state=0;
		all_aliens[num].x++;
		all_aliens[num].y++;
		break;
	}
}

/* Checks collision for all aliens */
/* Return -1 if none, otherwise alien number */
int collide_aliens(int x, int y)
{
	int i;
	for (i=0;i<NUM_ALIENS;i++)
	{
		if (all_aliens[i].type!=AT_NONE)
		{
			int mask_x, mask_y;
			mask_x = x-all_aliens[i].x;
			mask_y = y-all_aliens[i].y;
			if ((mask_y>=0) && (mask_y<MAX_HEIGHT) && (mask_x>=0) && (mask_x<8))
			{
				if ( (all_aliens[i].collide[mask_y] & (0x80 >> mask_x)) != 0 )
					return i;
			}
		}
	}
	return -1;
}
