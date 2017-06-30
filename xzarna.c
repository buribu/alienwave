/* This file is part of Alienwave, a game by Alessandro Pira */
#include "xzarna.h"
#include "aliens.h"
#include "blit.h"
#include "util.h"
#include "defs.h"

extern int x_ofs;
extern int y_ofs;
extern int score;
extern alien all_aliens[NUM_ALIENS];
extern const bitmask bitmask_tiny_alien;

const s_bitmask s_bitmask_xzarna  = {0x7FC0,0xFFE0,0x7FC0,0x3F80,0x7FC0};

alien_queen xzarna;

void start_xzarna()
{
	xzarna.enabled = 1;
}

int xzarna_exploding()
{
	return (xzarna.damage <= 0);
}

void init_queen()
{
	int i;
	xzarna.enabled = 0;
	xzarna.x = rrand(10,60);
	xzarna.y = -(QUEEN_HEIGHT + 1);
	xzarna.blit = blit_xzarna;
	xzarna.clear = clear_xzarna;
	xzarna.damage = MAX_DAMAGE;
	xzarna.eggs = 0x0F;
	for (i=0;i<QUEEN_HEIGHT;i++)
		xzarna.collide[i]=s_bitmask_xzarna[i];
}

int collide_queen(int x, int y, int type)
{
	if (xzarna.enabled)
	{
		int rel_x, rel_y;
		int ret=-1;

		rel_x = x - xzarna.x;
		rel_y = y - xzarna.y;
		if ( (rel_x >= 0) && (rel_x < 16) &&
		     (rel_y >= 0) && (rel_y < QUEEN_HEIGHT) )
		{
			if ( (xzarna.collide[rel_y] & (0x8000 >> rel_x)) != 0 )
			{
				int living;
				living = (xzarna.damage>0);
				ret = 1;
				switch (type)
				{
				case COL_FIRE:
					xzarna.damage -= 5;
					break;
				case COL_SHIELD:
					xzarna.damage -= 1;
					break;
				case COL_SHIP:
					break;
				}

				/* Control if Xzarna dies */
				if ((living) && (xzarna.damage<=0))
				{
					score+=5000;
				}
			}
		}

		return ret;
	}
	else return -1;
}

/* returns alien number */
int fire_egg(unsigned char *eggs)
{
	int ret;
	if (*eggs & 0x02)
	{
		ret = 1;
		if (all_aliens[ret].type != AT_NONE)
		{
			return -1;
		}
		*eggs &= 0x0D;
	}
	else if (*eggs & 0x04)
	{
		ret = 2;
		if (all_aliens[ret].type != AT_NONE)
		{
			return -1;
		}
		*eggs &= 0x0B;
	}
	else if (*eggs & 0x01)
	{
		ret = 0;
		if (all_aliens[ret].type != AT_NONE)
		{
			return -1;
		}
		*eggs &= 0x0E;
	}
	else if (*eggs & 0x08)
	{
		ret = 4;
		if (all_aliens[ret].type != AT_NONE)
		{
			return -1;
		}
		*eggs &= 0x07;
	}
	else return -1;

	return ret;
}

void recover_egg(unsigned char *eggs)
{
	if ((*eggs & 0x08)==0)
	{
		*eggs |= 0x08;
	}
	else if ((*eggs & 0x01)==0)
	{
		*eggs |= 0x01;
	}
	else if ((*eggs & 0x04)==0)
	{
		*eggs |= 0x04;
	}
	else if ((*eggs & 0x02)==0)
	{
		*eggs |= 0x02;
	}
}

/* This function moves Xzarna.
She floats left and right on the top of the screen, randomly sweeping down.
*/
void move_xzarna(void *q_ptr)
{
	static int xs=1;
	static int ys=0;
	alien_queen *al;
	al = (alien_queen *)q_ptr;

	if (al->enabled)
	{
		if (al->damage > 0)
		{
			if (al->y < 2)
			{
				ys = 1;
			}
			else if (al->y == 2)
			{
				if (rrand(1,100)>95)
				{
					ys = 1;
				}
				else
				{
					ys = 0;
				}
			}
			else if (al->y > (24-QUEEN_HEIGHT))
			{
				ys = -1;
			}

			if ( (al->x==0) || (al->x==69) )
			{
				xs = -xs;
			}

			al->y += ys;
			al->x += xs;

			if ( (al->y < 10) && (al->eggs > 0) && (rrand(1,100)>95) )
			{
				int n,i;
				n = fire_egg(&(al->eggs));
				/* Create egg */
				if (n>=0)
				{
					all_aliens[n].type = AT_TINY;
					all_aliens[n].blit = blit_tiny_alien;
					all_aliens[n].clear = clear_tiny_alien;
					for (i=0;i<MAX_HEIGHT;i++)
						all_aliens[n].collide[i] = bitmask_tiny_alien[i];
					all_aliens[n].state = -1;
					all_aliens[n].x = al->x+5;
					all_aliens[n].y = al->y+5;
					all_aliens[n].move = move_alien_straight;
				}
			}
			else if (rrand(1,100)>95)
			{
				recover_egg(&(al->eggs));
			}
		}
		else
		{
			int i;
			for (i=0;i<4;i++)
			{
				if (all_aliens[i].type==AT_NONE)
				{
					all_aliens[i].type=AT_BIG_EXP;
					all_aliens[i].state=0;
					all_aliens[i].blit=blit_explosion_3;
					all_aliens[i].clear=clear_explosion_3;
					all_aliens[i].x=rrand(al->x,al->x+9);
					all_aliens[i].y=rrand(al->y,al->y+5);
				}
			}
		}
	}
}

void move_queen()
{
	move_xzarna(&xzarna);
}

/* This function calculates the extra blitting element for Xzarna
(eye color and eggs) */
unsigned int xzarna_extra(alien_queen *al)
{
	unsigned int ret=0;
	if (al->damage > (60*MAX_DAMAGE/100)) ret=COL_GREEN;
	else if (al->damage > (20*MAX_DAMAGE/100)) ret=COL_YELLOW;
	else ret=COL_RED;

	ret |= (al->eggs) << 8;

	return ret;
}

void blit_queen()
{
	if (xzarna.enabled)
	{
		xzarna.blit(xzarna.x+x_ofs,xzarna.y+y_ofs,xzarna_extra(&xzarna));
	}
}

void delete_queen()
{
	if (xzarna.enabled)
	{
		xzarna.clear(xzarna.x+x_ofs,xzarna.y+y_ofs);
	}
}

