/* This file is part of Alienwave, a game by Alessandro Pira */

#include "shield.h"
#include "blit.h"
#include "aliens.h"
#include "xzarna.h"
#include "defs.h"

shield scudo;
// "scudo" is the italian word for shield

extern int x_ofs;
extern int y_ofs;
extern alien all_aliens[NUM_ALIENS];

void init_shields()
{
	scudo.x = -5;
	scudo.state = SHIELD_MIN; // Down and recharging
	scudo.blit = blit_shield;
	scudo.clear = clear_shield;
}

void open_shields(int x, int y)
{
	if ( (scudo.state>0) && (scudo.x<-1) )
	{
		scudo.x = x;
		scudo.y = y;
	}
}

void blit_shields()
{
	if (scudo.x >= -1)
	{
		scudo.blit(scudo.x+x_ofs,scudo.y+y_ofs,(scudo.state/SHIELD_STEP)+1);
	}
	else if (scudo.state>0) blit_shield_charge(x_ofs,y_ofs,scudo.state/(SHIELD_MAX/20));
}

void clear_shields()
{
	if (scudo.x >= -1)
	{
		scudo.clear(scudo.x+x_ofs,scudo.y+y_ofs);
	}
	clear_shield_charge(x_ofs,y_ofs);
}

void move_shields()
{
	if (scudo.x<-1)
	{
		if (scudo.state<SHIELD_MAX)
			scudo.state++;
	}
	else // The shield is on
	{
		scudo.state--;
		if (scudo.state>0)
		{
			int i,rel_x,rel_y;
			/* collision check */
			for (i=0;i<NUM_ALIENS;i++)
			{
				rel_x=scudo.x-all_aliens[i].x;
				rel_y=scudo.y-all_aliens[i].y;
				if ( (rel_y>=0) && (rel_y<MAX_HEIGHT) &&
				     (rel_x > -9) && (rel_x < 8) )
				{
					int shift;
					if (rel_x >= -1) shift=0x1FF>>(rel_x+1);
					else shift=0x1FF<<(-(rel_x+1));
					if ((all_aliens[i].collide[rel_y] & shift) != 0 )
					{
						blow_alien(i);
					}
				}
			}
			for (i=0;i<9;i++)
				collide_queen(scudo.x+i,scudo.y,COL_SHIELD);
		}
		else
		{
			scudo.state = SHIELD_MIN;
			scudo.x = -5;
		}
	}
}

